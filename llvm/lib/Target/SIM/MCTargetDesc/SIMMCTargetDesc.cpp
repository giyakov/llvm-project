//===-- SIMMCTargetDesc.cpp - SIM Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides SIM specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "SIMMCTargetDesc.h"
#include "SIMInstPrinter.h"
#include "SIMMCAsmInfo.h"
#include "TargetInfo/SIMTargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "SIMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SIMGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SIMGenRegisterInfo.inc"

static MCInstrInfo *createSIMMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitSIMMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createSIMMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createSIMMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "generic";
  StringRef TuneCPU = "generic";
  return createSIMMCSubtargetInfoImpl(TT, CPUName, TuneCPU, FS);
}

static MCInstPrinter *createSIMMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new SIMInstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createSIMMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new SIMMCAsmInfo(TT);

  unsigned WP = MRI.getDwarfRegNum(SIM::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, WP, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

extern "C" void LLVMInitializeSIMTargetMC() {
  for (Target *T : {&getTheSIMTarget()}) {
    // Register the MC asm info.
    TargetRegistry::RegisterMCAsmInfo(*T, createSIMMCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createSIMMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createSIMMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createSIMMCSubtargetInfo);

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T, createSIMMCInstPrinter);
  }
}
