//===-- SIMMCAsmInfo.h - SIM Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the SIMMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H
#define LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class SIMMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit SIMMCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCASMINFO_H
