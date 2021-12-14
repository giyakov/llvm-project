//===-- SIMInstrInfo.h - SIM Instruction Information ----------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
#define LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H

#include "SIM.h"
#include "SIMRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "SIMGenInstrInfo.inc"

namespace llvm {

class SIMInstrInfo : public SIMGenInstrInfo {
public:
  explicit SIMInstrInfo(const SIMSubtarget &STI);

protected:
  const SIMSubtarget &Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
