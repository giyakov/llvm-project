add_llvm_component_group(SIM)

set(LLVM_TARGET_DEFINITIONS SIM.td)

tablegen(LLVM SIMGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SIMGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SIMGenCodeEmitter.inc -gen-emitter)
tablegen(LLVM SIMGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM SIMGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SIMGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SIMGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SIMGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SIMGenMCPseudoLowering.inc -gen-pseudo-lowering)

# SIMCommonTableGen must be defined
add_public_tablegen_target(SIMCommonTableGen)

# SIMCodeGen should match with LLVMBuild.txt SIMCodeGen
add_llvm_target(SIMCodeGen
  SIMAsmPrinter.cpp
  SIMFrameLowering.cpp
  SIMInstrInfo.cpp
  SIMISelLowering.cpp
  SIMRegisterInfo.cpp
  SIMSubtarget.cpp
  SIMTargetObjectFile.cpp
  SIMISelDAGToDAG.cpp
  SIMTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  SIMDesc
  SIMInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  SIM
)

# Should match with "subdirectories =  MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
