//=== SIMMachineFunctionInfo.h - Private data used for SIM ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the SIM specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTION_H
#define LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTION_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// SIMFunctionInfo - This class is derived from MachineFunction private
/// SIM target-specific information for each MachineFunction.
class SIMFunctionInfo : public MachineFunctionInfo {
private:
  MachineFunction &MF;

public:
  SIMFunctionInfo(MachineFunction &MF) : MF(MF) {}
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTION_H
