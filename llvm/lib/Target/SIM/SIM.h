//=== SIM.h - Top-level interface for SIM representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM SIM backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_SIM_H
#define LLVM_LIB_TARGET_SIM_SIM_H

#include "MCTargetDesc/SIMMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {
class FunctionPass;
class SIMTargetMachine;
class FunctionPass;
class USimSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;
  
bool lowerSIMMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                  AsmPrinter &AP);
bool LowerSIMMachineOperandToMCOperand(const MachineOperand &MO,
                                       MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createSIMISelDag(SIMTargetMachine &TM, CodeGenOpt::Level OptLevel);

namespace SIM {
enum {
  GP = SIM::R0,
  RA = SIM::R1,
  SP = SIM::R2,
  FP = SIM::R3,
  BP = SIM::R4,
};
} // namespace SIM

} // end namespace llvm;

#endif // end LLVM_LIB_TARGET_SIM_SIM_H
