//===-- SIMRegisterInfo.cpp - SIM Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SIM implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "SIMRegisterInfo.h"
#include "SIM.h"
#include "SIMInstrInfo.h"
#include "SIMSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "SIM-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "SIMGenRegisterInfo.inc"

SIMRegisterInfo::SIMRegisterInfo() : SIMGenRegisterInfo(SIM::RA) {}

const MCPhysReg *
SIMRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SIM_SaveList;
}

// TODO: check cconv
BitVector SIMRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  SIMFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(SIM::GP);
  Reserved.set(SIM::SP);

  if (TFI->hasFP(MF)) {
    Reserved.set(SIM::FP);
  }
  if (TFI->hasBP(MF)) {
    Reserved.set(SIM::BP);
  }
  return Reserved;
}

bool SIMRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

void SIMRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
}

Register SIMRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? SIM::FP : SIM::SP;
}

const uint32_t *
SIMRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const {
  return CSR_SIM_RegMask;
}
