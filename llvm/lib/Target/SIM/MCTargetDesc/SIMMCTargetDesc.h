//===-- SIMMCTargetDesc.h - SIM Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides SIM specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H
#define LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H

// Defines symbolic names for SIM registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "SIMGenRegisterInfo.inc"

// Defines symbolic names for the SIM instructions.
#define GET_INSTRINFO_ENUM
#include "SIMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "SIMGenSubtargetInfo.inc"

#endif // end LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H
