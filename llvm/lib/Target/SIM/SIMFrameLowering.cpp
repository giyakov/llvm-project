//===-- SIMFrameLowering.cpp - SIM Frame Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SIMTargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "SIMFrameLowering.h"
#include "SIMSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

// hasFP - Return true if the specified function should have a dedicated frame
// pointer register.  This is true if the function has variable sized allocas,
// if it needs dynamic stack realignment, if frame pointer elimination is
// disabled, or if the frame address is taken.
bool SIMFrameLowering::hasFP(const MachineFunction &MF) const {
  return false;
}

MachineBasicBlock::iterator SIMFrameLowering::eliminateCallFramePseudoInstr(
                                        MachineFunction &MF,
                                        MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator I) const {
  return MBB.erase(I);
}

void SIMFrameLowering::emitPrologue(MachineFunction &MF,
                                     MachineBasicBlock &MBB) const {
}

void SIMFrameLowering::emitEpilogue(MachineFunction &MF,
                                     MachineBasicBlock &MBB) const {
}

bool
SIMFrameLowering::hasReservedCallFrame(const MachineFunction &MF) const {
  return true;
}

// This method is called immediately before PrologEpilogInserter scans the
// physical registers used to determine what callee saved registers should be
// spilled. This method is optional.
void SIMFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                              BitVector &SavedRegs,
                                              RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
}
