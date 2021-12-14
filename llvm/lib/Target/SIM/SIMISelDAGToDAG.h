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

#include "SIMSubtarget.h"
#include "SIMTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
class SIMDAGToDAGISel : public SelectionDAGISel {
public:
  explicit SIMDAGToDAGISel(SIMTargetMachine &TM, CodeGenOpt::Level OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  // Pass Name
  StringRef getPassName() const override {
    return "CPU0 DAG->DAG Pattern Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "SIMGenDAGISel.inc"

private:
  const SIMSubtarget *Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_SIM_SIMISELDAGTODAG_H
