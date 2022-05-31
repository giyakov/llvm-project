//===-- SIMISelDAGToDAG.cpp - A Dag to Dag Inst Selector for SIM ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the SIM target.
//
//===----------------------------------------------------------------------===//

#include "SIMISelDAGToDAG.h"
#include "MCTargetDesc/SIMMCAsmInfo.h"
#include "SIM.h"
#include "SIMTargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "sim-isel"

/// This pass converts a legalized DAG into a SIM-specific DAG, ready for
/// instruction scheduling.
FunctionPass *llvm::createSIMISelDag(SIMTargetMachine &TM,
                                      CodeGenOpt::Level OptLevel) {
  return new SIMDAGToDAGISel(TM, OptLevel);
}

bool SIMDAGToDAGISel::SelectAddrFI(SDValue Addr, SDValue &Base) {
  if (auto *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), MVT::i32);
    return true;
  }
  return false;
}

bool SIMDAGToDAGISel::SelectBaseAddr(SDValue Addr, SDValue &Base) {
  if (auto *FIN = dyn_cast<FrameIndexSDNode>(Addr))
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), MVT::i32);
  else
    Base = Addr;
  return true;
}

void SIMDAGToDAGISel::Select(SDNode *Node) {
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(dbgs() << "== "; Node->dump(CurDAG); dbgs() << "\n");
    Node->setNodeId(-1);
    return;
  }
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);
  MVT VT = Node->getSimpleValueType(0);

  switch (Opcode) {
  case ISD::FrameIndex: {
    SDValue Imm = CurDAG->getTargetConstant(0, DL, MVT::i32);
    int FI = cast<FrameIndexSDNode>(Node)->getIndex();
    SDValue TFI = CurDAG->getTargetFrameIndex(FI, VT);
    ReplaceNode(Node, CurDAG->getMachineNode(SIM::ADDI, DL, VT, TFI, Imm));
    return;
  }
  case ISD::Constant: {
    auto *ConstNode = cast<ConstantSDNode>(Node);
    assert(VT == MVT::i32);
    int64_t Imm = ConstNode->getSExtValue();
    SDNode *Res = nullptr;
    if (isInt<16>(Imm)) {
      SDValue SDImm = CurDAG->getTargetConstant(Imm, DL, MVT::i32);
      Res = CurDAG->getMachineNode(SIM::MOVLIs, DL, VT, SDImm);
    } else {
      // (h' << 16) + (l >> 15) * (-1 << 16) + l
      // ((h' + (l >> 15) * (-1 << 16)) + l
      // h + l,  h' = h - (l >> 15) * (-1 << 16)
      uint16_t ImmLi = (uint64_t)Imm & 0xffff;
      uint16_t ImmHi = ((uint64_t)Imm >> 16) - ((ImmLi >> 15) ? 0xffff : 0);
      SDValue SDImmLi = CurDAG->getTargetConstant(ImmLi, DL, MVT::i32);
      SDValue SDImmHi = CurDAG->getTargetConstant(ImmHi, DL, MVT::i32);
      Res = CurDAG->getMachineNode(SIM::MOVHI, DL, VT, SDImmHi);
      Res =
          CurDAG->getMachineNode(SIM::ADDI, DL, VT, SDValue(Res, 0), SDImmLi);
    }
    ReplaceNode(Node, Res);
    return;
  }
  }
  SelectCode(Node);
}
