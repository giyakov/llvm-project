//===---- SIMISelDAGToDAG.h - A Dag to Dag Inst Selector for SIM ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the SIM target.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_SIMISELDAGTODAG_H
#define LLVM_LIB_TARGET_SIM_SIMISELDAGTODAG_H

#include "MCTargetDesc/SIMMCAsmInfo.h"
#include "SIMSubtarget.h"
#include "SIMTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
class SIMDAGToDAGISel : public SelectionDAGISel {
public:
  SIMDAGToDAGISel(SIMTargetMachine &TM, CodeGenOpt::Level OptLevel)
      : SelectionDAGISel(TM, OptLevel) {}

  bool runOnMachineFunction(MachineFunction &MF) override {
    Subtarget = &MF.getSubtarget<SIMSubtarget>();
    return SelectionDAGISel::runOnMachineFunction(MF);
  }

  bool SelectAddrFI(SDValue Addr, SDValue &Base);
  bool SelectBaseAddr(SDValue Addr, SDValue &Base);

  void Select(SDNode *N) override;

  StringRef getPassName() const override {
    return "SIM DAG->DAG Pattern Instruction Selection";
  }

  static SIMCC::CondCode getSIMCCForIntCC(ISD::CondCode CC) {
    switch (CC) {
    case ISD::SETEQ:
      return SIMCC::EQ;
    case ISD::SETNE:
      return SIMCC::NE;
    case ISD::SETLE:
      return SIMCC::LE;
    case ISD::SETGT:
      return SIMCC::GT;
    case ISD::SETULE:
      return SIMCC::LEU;
    case ISD::SETUGT:
      return SIMCC::GTU;
    default:
      llvm_unreachable("");
    }
  }

#include "SIMGenDAGISel.inc"

private:
  const SIMSubtarget *Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_SIM_SIMISELDAGTODAG_H
