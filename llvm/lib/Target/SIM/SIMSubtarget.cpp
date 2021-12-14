//===-- SIMSubtarget.cpp - SIM Subtarget Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the SIM specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "SIM.h"
#include "SIMSubtarget.h"
#include "SIMMachineFunction.h"
#include "SIMRegisterInfo.h"
#include "SIMTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "sim-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SIMGenSubtargetInfo.inc"

SIMSubtarget::SIMSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : SIMGenSubtargetInfo(TT, CPU, "generic", FS),
      TSInfo(),
      InstrInfo(initializeSubtargetDependencies(TT, CPU, FS, TM)),
      FrameLowering(*this),
      TLInfo(TM, *this),
      RegInfo(*this) { }


SIMSubtarget &
SIMSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef FS,
                                                const TargetMachine &TM) {
  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, "generic", FS);

  return *this;
}
