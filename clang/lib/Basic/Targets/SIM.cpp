//===--- SIM.cpp - Implement SIM target feature support ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements SIMTargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "SIM.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

const char *const SIMTargetInfo::GCCRegNames[] = {
  // Integer registers
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
  "r10", "r11", "r12", "r13", "r14", "r15"
};

const TargetInfo::GCCRegAlias GCCRegAliases[] = {
  {{"r0"},  "R0"},
  {{"r1"},  "R1"},
  {{"r2"},  "R2"},
  {{"r3"},  "R3"},
  {{"r4"},  "R4"},
  {{"r5"},  "R5"},
  {{"r6"},  "R6"},
  {{"r7"},  "R7"},
  {{"r8"},  "R8"},
  {{"r9"},  "R9"},
  {{"r10"}, "R10"},
  {{"r11"}, "R11"},
  {{"r12"}, "R12"},
  {{"r13"}, "R13"},
  {{"r14"}, "R14"},
  {{"r15"}, "R15"},
};

ArrayRef<const char *> SIMTargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

ArrayRef<TargetInfo::GCCRegAlias> SIMTargetInfo::getGCCRegAliases() const {
  return llvm::makeArrayRef(GCCRegAliases);
}

void SIMTargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  // Define the __SIM__ macro when building for this target
  Builder.defineMacro("__SIM__");
}
