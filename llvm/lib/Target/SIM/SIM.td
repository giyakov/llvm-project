//=== SIM.td - Describe the SIM Target Machine ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Top tablegen file that pulls in code from the LLVM framework along with
// code specific to this target.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions, Register information, etc
//===----------------------------------------------------------------------===//

include "SIMSchedule.td"
include "SIMRegisterInfo.td"
include "SIMCallingConv.td"
include "SIMInstrInfo.td"

def SIMInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// SIM processors supported
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic",  NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// SIM Target declaration
//===----------------------------------------------------------------------===//

def SIM : Target {
  let InstructionSet = SIMInstrInfo;
}
