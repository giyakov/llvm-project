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
  virtual void anchor();

  bool ReturnStackOffsetSet = false;
  unsigned ReturnStackOffset = -1U;

  /// FrameIndex for start of varargs area
  int VarArgsFrameIndex = 0;
  /// Size of the save area used for varargs
  int VarArgsSaveSize = 0;
  /// Size of stack frame to save callee saved registers
  unsigned CalleeSavedStackSize = 0;

public:
  SIMFunctionInfo();
  explicit SIMFunctionInfo(MachineFunction &MF);
  ~SIMFunctionInfo() override;

  void setVarArgsFrameIndex(int Off);
  int getVarArgsFrameIndex() const;

  void setVarArgsSaveSize(int Size);
  int getVarArgsSaveSize() const;

  unsigned getCalleeSavedStackSize() const;
  void setCalleeSavedStackSize(unsigned Size);

  void setReturnStackOffset(unsigned Off);

  unsigned getReturnStackOffset() const;
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTION_H
