//===--- SIM.h - Declare SIM target feature support ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares SIMTargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_SIM_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_SIM_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY SIMTargetInfo : public TargetInfo {
public:
  SIMTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
    : TargetInfo(Triple) {
    NoAsmVariants = true;

    constexpr auto DEFAULT_ALIGNMENT = 32;
    LongLongAlign = DEFAULT_ALIGNMENT;
    DoubleAlign = DEFAULT_ALIGNMENT;
    LongDoubleAlign = DEFAULT_ALIGNMENT;

    SuitableAlign = DEFAULT_ALIGNMENT;

    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;

    UseZeroLengthBitfieldAlignment = true;
    // Description string has to be kept in sync with backend string at
    // llvm/lib/Target/SIM/SIMTargetMachine.cpp
    resetDataLayout(// Little endian
                    "e"
                    // ELF name mangling
                    "-m:e"
                    // Type:SizeInBits:StoreSizeInBits:AllocSizeInBits
                    "-p:32:32" // pointer
                    "-i1:8:32" // int
                    "-i8:8:32" // int
                    "-i16:16:32" // int
                    "-i32:32:32" // int
                    "-i64:32" // int
                    "-f32:32:32" // float
                    "-f64:32" // float
                    "-a:0:32" // aggregate
                    // 32-bit native integer width i.e register are 32-bit
                    "-n32"
                    // 32-bit natural stack alignment
                    "-S32"
    );
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return None;
  }

  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return None;
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  const char *getClobbers() const override {
    return "";
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    return false;
  }

  ArrayRef<const char *> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
        "r0", "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7", "r8",
        "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16"};
    return llvm::makeArrayRef(GCCRegNames);
  }

  bool isCLZForZeroUndef() const override { return false; }

};

} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_SIM_H
