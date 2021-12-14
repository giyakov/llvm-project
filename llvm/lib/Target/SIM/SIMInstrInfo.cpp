//===-- SIMInstrInfo.cpp - SIM Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SIM implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "SIMInstrInfo.h"

#include "SIMTargetMachine.h"
#include "SIMMachineFunction.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define DEBUG_TYPE "sim-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "SIMGenInstrInfo.inc"

SIMInstrInfo::SIMInstrInfo(const SIMSubtarget &STI)
    : SIMGenInstrInfo(SIM::ADJCALLSTACKDOWN, SIM::ADJCALLSTACKUP),
      Subtarget(STI)
{
}
