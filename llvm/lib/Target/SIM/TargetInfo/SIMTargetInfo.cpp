//===-- SIMTargetInfo.cpp - SIM Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/SIMTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheSIMTarget() {
  static Target TheSIMTarget;
  return TheSIMTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSIMTargetInfo() {
  RegisterTarget<Triple::sim> X(getTheSIMTarget(), "sim",
                                  "32-bit SIM cpu", "SIM");
}
