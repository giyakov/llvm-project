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
#include "SIMSubtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "SIMGenRegisterInfo.inc"

#define DEBUG_TYPE "sim-reginfo"

using namespace llvm;

SIMRegisterInfo::SIMRegisterInfo(const SIMSubtarget &ST)
  : SIMGenRegisterInfo(SIM::X1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
SIMRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return SIM_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *SIMRegisterInfo::intRegClass(unsigned Size) const {
  return &SIM::GPRRegClass;
}

const uint32_t *
SIMRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return SIM_CalleeSavedRegs_RegMask;
}

BitVector SIMRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, SIM::X0); // zero
  markSuperRegs(Reserved, SIM::X2); // sp
  markSuperRegs(Reserved, SIM::X3); // gp
  markSuperRegs(Reserved, SIM::X4); // tp

  return Reserved;
}

void SIMRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj,
                                           unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
}

bool
SIMRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
SIMRegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
SIMRegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
SIMRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register SIMRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  llvm_unreachable("Unsupported getFrameRegister");
}

