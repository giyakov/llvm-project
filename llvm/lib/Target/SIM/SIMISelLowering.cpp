//===-- SIMISelLowering.cpp - SIM DAG Lowering Implementation -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that SIM uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "SIMISelLowering.h"
#include "MCTargetDesc/SIMMCAsmInfo.h"
#include "SIM.h"
#include "SIMRegisterInfo.h"
#include "SIMSubtarget.h"
#include "SIMTargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/Register.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MachineValueType.h"
#include <algorithm>

#define DEBUG_TYPE "sim-lower"

using namespace llvm;

static const MCPhysReg ArgGPRs[] = {SIM::R9, SIM::R10, SIM::R11, SIM::R12};

void SIMTargetLowering::ReplaceNodeResults(SDNode *N,
                                            SmallVectorImpl<SDValue> &Results,
                                            SelectionDAG &DAG) const {
  llvm_unreachable("");
}

SIMTargetLowering::SIMTargetLowering(const TargetMachine &TM,
                                     const SIMSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  addRegisterClass(MVT::i32, &SIM::GPRRegClass);

  computeRegisterProperties(STI.getRegisterInfo());

  setStackPointerRegisterToSaveRestore(SIM::R2);

  for (unsigned Opc = 0; Opc < ISD::BUILTIN_OP_END; ++Opc)
    setOperationAction(Opc, MVT::i32, Expand);

  setOperationAction(ISD::ADD, MVT::i32, Legal);
  setOperationAction(ISD::SUB, MVT::i32, Legal);
  setOperationAction(ISD::MUL, MVT::i32, Legal);
  setOperationAction(ISD::SDIV, MVT::i32, Legal);
  setOperationAction(ISD::UDIV, MVT::i32, Legal);
  setOperationAction(ISD::SREM, MVT::i32, Legal);
  setOperationAction(ISD::UREM, MVT::i32, Legal);
  setOperationAction(ISD::OR, MVT::i32, Legal);
  setOperationAction(ISD::AND, MVT::i32, Legal);
  setOperationAction(ISD::XOR, MVT::i32, Legal);
  setOperationAction(ISD::SHL, MVT::i32, Legal);
  setOperationAction(ISD::SRL, MVT::i32, Legal);
  setOperationAction(ISD::SRA, MVT::i32, Legal);

  setOperationAction(ISD::LOAD, MVT::i32, Legal);
  setOperationAction(ISD::STORE, MVT::i32, Legal);

  setOperationAction(ISD::Constant, MVT::i32, Legal);
  setOperationAction(ISD::UNDEF, MVT::i32, Legal);

  setOperationAction(ISD::BR_CC, MVT::i32, Custom);
  setOperationAction(ISD::SELECT_CC, MVT::i32, Custom);

  setOperationAction(ISD::FRAMEADDR, MVT::i32, Legal);
}

const char *SIMTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case SIMISD::CALL:
    return "SIMISD::CALL";
  case SIMISD::RET:
    return "SIMISD::RET";
  }
  return nullptr;
}

/// LowerFormalArguments - transform physical registers into virtual registers
/// and generate load operations for arguments places on the stack.
SDValue SIMTargetLowering::LowerFormalArguments(
                                    SDValue Chain,
                                    CallingConv::ID CallConv,
                                    bool isVarArg,
                                    const SmallVectorImpl<ISD::InputArg> &Ins,
                                    const SDLoc &dl, SelectionDAG &DAG,
                                    SmallVectorImpl<SDValue> &InVals) const
{
  llvm_unreachable("");
  return SDValue();
}

//===----------------------------------------------------------------------===//
//@              Return Value Calling Convention Implementation
//===----------------------------------------------------------------------===//

bool SIMTargetLowering::CanLowerReturn(CallingConv::ID CallConv,
                                MachineFunction &MF, bool isVarArg,
                                const SmallVectorImpl<ISD::OutputArg> &Outs,
                                LLVMContext &Context) const
{
  llvm_unreachable("");
  return false;
}

/// LowerMemOpCallTo - Store the argument to the stack.
SDValue SIMTargetLowering::LowerMemOpCallTo(SDValue Chain,
                                              SDValue Arg, const SDLoc &dl,
                                              SelectionDAG &DAG,
                                              const CCValAssign &VA,
                                              ISD::ArgFlagsTy Flags) const {
  llvm_unreachable("Cannot store arguments to stack");
}

/// LowerCallResult - Lower the result values of a call into the
/// appropriate copies out of appropriate physical registers.
SDValue
SIMTargetLowering::LowerCallResult(SDValue Chain, SDValue InFlag,
                                     CallingConv::ID CallConv, bool isVarArg,
                                     const SmallVectorImpl<ISD::InputArg> &Ins,
                                     const SDLoc &dl, SelectionDAG &DAG,
                                     SmallVectorImpl<SDValue> &InVals,
                                     bool isThisReturn, SDValue ThisVal) const {
  llvm_unreachable("");
  return SDValue();
}

SDValue SIMTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                       SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("Cannot lower call");
}

/// HandleByVal - Every parameter *after* a byval parameter is passed
/// on the stack.  Remember the next parameter register to allocate,
/// and then confiscate the rest of the parameter registers to insure
/// this.
void SIMTargetLowering::HandleByVal(CCState *State, unsigned &Size,
                                    Align align) const {
  llvm_unreachable("");
}

SDValue
SIMTargetLowering::LowerReturn(SDValue Chain,
                                 CallingConv::ID CallConv, bool isVarArg,
                                 const SmallVectorImpl<ISD::OutputArg> &Outs,
                                 const SmallVectorImpl<SDValue> &OutVals,
                                 const SDLoc &dl, SelectionDAG &DAG) const {
  llvm_unreachable("");
  return SDValue();
}

//===----------------------------------------------------------------------===//
//  Lower helper functions
//===----------------------------------------------------------------------===//

SDValue SIMTargetLowering::getGlobalAddressWrapper(SDValue GA,
                                                     const GlobalValue *GV,
                                                     SelectionDAG &DAG) const {
  llvm_unreachable("Unhandled global variable");
}

//===----------------------------------------------------------------------===//
//  Misc Lower Operation implementation
//===----------------------------------------------------------------------===//

SDValue SIMTargetLowering::
LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const {
  llvm_unreachable("Unsupported global address");
}

SDValue SIMTargetLowering::
LowerConstantPool(SDValue Op, SelectionDAG &DAG) const {
  llvm_unreachable("Unsupported constant pool");
}

SDValue SIMTargetLowering::
LowerBlockAddress(SDValue Op, SelectionDAG &DAG) const {
  llvm_unreachable("Unsupported block address");
}

SDValue
SIMTargetLowering::LowerRETURNADDR(SDValue Op, SelectionDAG &DAG) const {
  return SDValue();
}

SDValue
SIMTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  llvm_unreachable("unimplemented");
}
