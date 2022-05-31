#include "SIMMachineFunction.h"

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

SIMFunctionInfo::SIMFunctionInfo() {}
SIMFunctionInfo::SIMFunctionInfo(MachineFunction &MF) {}
SIMFunctionInfo::~SIMFunctionInfo() {}

void SIMFunctionInfo::anchor() {}

void SIMFunctionInfo::setVarArgsFrameIndex(int Off) { VarArgsFrameIndex = Off; }
int SIMFunctionInfo::getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

void SIMFunctionInfo::setVarArgsSaveSize(int Size) { VarArgsSaveSize = Size; }
int SIMFunctionInfo::getVarArgsSaveSize() const { return VarArgsSaveSize; }

unsigned SIMFunctionInfo::getCalleeSavedStackSize() const { return CalleeSavedStackSize; }
void SIMFunctionInfo::setCalleeSavedStackSize(unsigned Size) { CalleeSavedStackSize = Size; }

void SIMFunctionInfo::setReturnStackOffset(unsigned Off) {
  assert(!ReturnStackOffsetSet && "Return stack offset set twice");
  ReturnStackOffset = Off;
  ReturnStackOffsetSet = true;
}

unsigned SIMFunctionInfo::getReturnStackOffset() const {
  assert(ReturnStackOffsetSet && "Return stack offset not set");
  return ReturnStackOffset;
}

}
