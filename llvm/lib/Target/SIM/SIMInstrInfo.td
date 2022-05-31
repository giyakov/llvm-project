//== SIMInstrInfo.td - Target Description for SIM Target -*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SIM implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

def SDT_SIMCall : SDTypeProfile<0, -1, [SDTCisVT<0, i32>]>;
def SDT_SIMCallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;
def SDT_SIMCallSeqEnd : SDCallSeqEnd<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;

def SDT_SIMBrCC : SDTypeProfile<0, 4, [SDTCisSameAs<0, 1>, SDTCisVT<2, OtherVT>,
                                       SDTCisVT<3, OtherVT>]>;
def SDT_SIMSelectCC : SDTypeProfile<1, 5, [SDTCisSameAs<1, 2>, SDTCisVT<3, OtherVT>,
                                           SDTCisSameAs<0, 4>, SDTCisSameAs<4, 5>]>;


// These are target-independent nodes, but have target-specific formats.
def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_SIMCallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;

def callseq_end : SDNode<"ISD::CALLSEQ_END",   SDT_SIMCallSeqEnd,
                         [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def sim_ret : SDNode<"SIMISD::RET", SDTNone,
                     [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def sim_call : SDNode<"SIMISD::CALL", SDT_SIMCall,
                      [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
                       SDNPVariadic]>;

def sim_brcc : SDNode<"SIMISD::BR_CC", SDT_SIMBrCC,
                      [SDNPHasChain]>;

def sim_selectcc : SDNode<"SIMISD::SELECT_CC", SDT_SIMSelectCC,
                          [SDNPInGlue]>;

include "SIMInstrFormats.td"

//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

let Defs = [R2], Uses = [R2] in {
def ADJCALLSTACKDOWN : SIMPseudoInst<(outs), (ins i32imm:$amt, i32imm:$amt2),
                                      "# ADJCALLSTACKDOWN $amt, $amt2",
                                      [(callseq_start timm:$amt, timm:$amt2)]>;
def ADJCALLSTACKUP : SIMPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                                    "# ADJCALLSTACKUP $amt1",
                                    [(callseq_end timm:$amt1, timm:$amt2)]>;
}

def IsOrAdd: PatFrag<(ops node:$A, node:$B), (or node:$A, node:$B), [{
  return isOrEquivalentToAdd(N);
}]>;

//===----------------------------------------------------------------------===//
// SIM Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

class ImmAsmOperand<string prefix, int width, string suffix> : AsmOperandClass {
  let Name = prefix # "Imm" # width # suffix;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

class SImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"S", width, suffix> {
}

class UImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"U", width, suffix> {
}

def imm32 : Operand<i32>;

def simm16 : Operand<i32>, ImmLeaf<i32, [{return isInt<16>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM16";
  let OperandNamespace = "SIMOp";
}

def uimm16 : Operand<i32>, ImmLeaf<i32, [{return isUInt<16>(Imm);}]> {
  let ParserMatchClass = UImmAsmOperand<16>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeUImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isUInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_UIMM16";
  let OperandNamespace = "SIMOp";
}

def btarget16 : Operand<OtherVT> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

def ctarget16 : Operand<i32> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

def LI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() & 0xffff,
                                   SDLoc(N), MVT::i32);
}]>;

def HI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() >> 16, SDLoc(N),
                                   MVT::i32);
}]>;

def i32li16u : Operand<i32>, PatLeaf<(i32 imm), [{
    return ((uint64_t)(N->getZExtValue() & 0xFFFFUL) == N->getZExtValue());}], LI16> {
}

def i32li16s : Operand<i32>, PatLeaf<(i32 imm), [{
    return ((int64_t)(N->getSExtValue() & 0xFFFFUL) == N->getSExtValue());}], LI16> {
}

def i32hi16 : Operand<i32>, PatLeaf<(i32 imm), [{
    return ((N->getZExtValue() & 0xFFFF0000UL) == N->getZExtValue());}], HI16> {
}

// Addressing modes
def AddrFI : ComplexPattern<iPTR, 1, "SelectAddrFI", [frameindex], []>;
def BaseAddr : ComplexPattern<iPTR, 1, "SelectBaseAddr">;

class PatGpr<SDPatternOperator OpNode, SIMInst Inst>
    : Pat<(OpNode GPR:$rs1), (Inst GPR:$rs1)>;
class PatGprGpr<SDPatternOperator OpNode, SIMInst Inst>
    : Pat<(OpNode GPR:$rs1, GPR:$rs2), (Inst GPR:$rs1, GPR:$rs2)>;
class PatGprImm<SDPatternOperator OpNode, SIMInst Inst, ImmLeaf ImmType>
    : Pat<(i32 (OpNode (i32 GPR:$rs1), ImmType:$imm)),
          (Inst GPR:$rs1, ImmType:$imm)>;

class PatBcc<CondCode Cond, SIMInst Inst>
    : Pat<(sim_brcc GPR:$rs1, GPR:$rs2, Cond, bb:$imm16),
          (Inst GPR:$rs1, GPR:$rs2, btarget16:$imm16)>;

//===----------------------------------------------------------------------===//
// Instructions specific format
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBranch = 1, isTerminator = 1 in
class BranchCC<bits<8> op, string opcodestr>
    : SIMInst<op, (outs), (ins GPR:$rs1, GPR:$rs2, btarget16:$imm16),
              !strconcat(opcodestr, "\t$rs1 $rs2 $imm16"), []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class ArithmRR<bits<8> op, string opcodestr>
    : SIMInst<op, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
              !strconcat(opcodestr, "\t$rd $rs1 $rs2"), []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class ArithmRI<bits<8> op, string opcodestr>
    : SIMInst<op, (outs GPR:$rd), (ins GPR:$rs1, simm16:$imm),
              !strconcat(opcodestr, "\t$rd $rs1 $imm"), []>;

//===----------------------------------------------------------------------===//
// SIM Instructions
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBarrier = 1, isBranch = 1, isTerminator = 1 in
def B : SIMInst<0x0, (outs), (ins btarget16:$imm16), "B\t$imm16",
                [(br bb:$imm16)]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1 in
def BR : SIMInst<0x0, (outs), (ins GPR:$rs1), "BR\t$rs1",
                 [(brind GPR:$rs1)]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1 in
def BL : SIMInst<0x0, (outs GPR:$rd), (ins ctarget16:$imm16), "BL\t$rd $imm16",
                 []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1 in
def BLR : SIMInst<0x0, (outs GPR:$rd), (ins GPR:$rs1),
                  "BLR\t$rd $rs1", []>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : SIMPseudoInst<(outs), (ins), "# PseudoRET",
                [(sim_ret)]>,
                PseudoInstExpansion<(BR R1)>;

let isCall = 1, Defs = [R1] in
def PseudoCALL : SIMPseudoInst<(outs), (ins ctarget16:$func), "# PseudoCALL",
                 [(sim_call tglobaladdr:$func)]>,
                 PseudoInstExpansion<(BL R1, ctarget16:$func)>;

let isCall = 1, Defs = [R1] in
def PseudoCALLInd : SIMPseudoInst<(outs), (ins GPR:$rs1), "# PseudoCALLInd",
                    [(sim_call GPR:$rs1)]>,
                    PseudoInstExpansion<(BLR R1, GPR:$rs1)>;

def BEQ : BranchCC<0x0, "B.EQ">;
def BNE : BranchCC<0x0, "B.NE">;
def BLE : BranchCC<0x0, "BLE">;
def BGT : BranchCC<0x0, "B.GT">;
def BLEU : BranchCC<0x0, "B.LEU">;
def BGTU : BranchCC<0x0, "B.GTU">;

def : PatBcc<SETEQ, BEQ>;
def : PatBcc<SETNE, BNE>;
def : PatBcc<SETLE, BLE>;
def : PatBcc<SETGT, BGT>;
def : PatBcc<SETULE, BLEU>;
def : PatBcc<SETUGT, BGTU>;

def IntCCtoSIMCC : SDNodeXForm<sim_selectcc, [{
  ISD::CondCode CC = cast<CondCodeSDNode>(N->getOperand(2))->get();
  SIMCC::CondCode BrCC = getSIMCCForIntCC(CC);
  return CurDAG->getTargetConstant(BrCC, SDLoc(N), MVT::i32);
}]>;

def sim_selectcc_frag : PatFrag<(ops node:$lhs, node:$rhs, node:$cc,
                                  node:$truev, node:$falsev),
                                  (sim_selectcc node:$lhs, node:$rhs,
                                    node:$cc, node:$truev, node:$falsev),
                                [{}], IntCCtoSIMCC>;

let usesCustomInserter = 1 in
def Select_CC_GPR
    : SIMPseudoInst<
      (outs GPR:$rd), (ins GPR:$lhs, GPR:$rhs, imm32:$imm, GPR:$st, GPR:$sf),
      "# PseudoSelect",
      [(set i32:$rd, (sim_selectcc_frag:$imm GPR:$lhs, GPR:$rhs, cond, GPR:$st, GPR:$sf))]>;

let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1 in
def MOVLIs : SIMInst<0x0, (outs GPR:$rd), (ins i32li16s:$imm),
                     "MOVli\t$rd $imm",
                     [(set GPR:$rd, i32li16s:$imm)]>;

let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1 in
def MOVHI : SIMInst<0x0, (outs GPR:$rd), (ins i32hi16:$imm),
                    "MOVhi\t$rd $imm",
                    [(set GPR:$rd, i32hi16:$imm)]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 1 in
def STI_: SIMInst<0x0, (outs), (ins GPR:$rs2, GPR:$rs1, simm16:$imm),
                  "STi\t$rs2 ${rs1} ${imm}", []>;
def : Pat<(store (i32 GPR:$rs2), BaseAddr:$rs1),
          (STI_ GPR:$rs2, BaseAddr:$rs1, 0)>;
def : Pat<(store (i32 GPR:$rs2), (add BaseAddr:$rs1, simm16:$imm)),
          (STI_ GPR:$rs2, BaseAddr:$rs1, simm16:$imm)>;
def : Pat<(store (i32 GPR:$rs2), (IsOrAdd AddrFI:$rs1, simm16:$imm)),
          (STI_ GPR:$rs2, AddrFI:$rs1, simm16:$imm)>;

let hasSideEffects = 0, mayLoad = 1, mayStore = 0 in
def LDI: SIMInst<0x0, (outs GPR:$rd), (ins GPR:$rs1, simm16:$imm),
                 "LDi\t$rd ${rs1} ${imm}", []>;

def : Pat<(i32 (load BaseAddr:$rs1)), (LDI BaseAddr:$rs1, 0)>;
def : Pat<(i32 (load (add BaseAddr:$rs1, simm16:$imm))),
          (LDI BaseAddr:$rs1, simm16:$imm)>;
def : Pat<(i32 (load (IsOrAdd AddrFI:$rs1, simm16:$imm))),
          (LDI AddrFI:$rs1, simm16:$imm)>;

def ADD  : ArithmRR<0x0, "ADD">;     def : PatGprGpr<add,  ADD>;
def SUB  : ArithmRR<0x0, "SUB">;     def : PatGprGpr<sub,  SUB>;
def MUL  : ArithmRR<0x0, "MUL">;     def : PatGprGpr<mul,  MUL>;
def DIVS : ArithmRR<0x0, "DIV">;     def : PatGprGpr<sdiv, DIVS>;
def REM  : ArithmRR<0x0, "DIV_REM">; def : PatGprGpr<srem, REM>;
def OR   : ArithmRR<0x0, "OR">;      def : PatGprGpr<or,   OR>;
def AND  : ArithmRR<0x0, "AND">;     def : PatGprGpr<and,  AND>;
def XOR  : ArithmRR<0x0, "XOR">;     def : PatGprGpr<xor,  XOR>;

def ADDI  : ArithmRI<0x0, "ADDi">;     def : PatGprImm<add, ADDI, simm16>;
def MULI  : ArithmRI<0x0, "MULi">;     def : PatGprImm<mul, MULI, simm16>;
def DIVIS : ArithmRI<0x0, "DIVi">;     def : PatGprImm<sdiv, DIVIS, simm16>;
def REMIS : ArithmRI<0x0, "DIV_REMi">; def : PatGprImm<srem, REMIS, simm16>;
def ORI   : ArithmRI<0x0, "ORi">;      def : PatGprImm<or, ORI, simm16>;
def ANDI  : ArithmRI<0x0, "ANDi">;     def : PatGprImm<and, ANDI, simm16>;
def XORI  : ArithmRI<0x0, "XORi">;     def : PatGprImm<xor, XORI, simm16>;

def SHL   : ArithmRR<0x0, "SHL">;   def : PatGprGpr<shl, SHL>;
def SHR   : ArithmRR<0x0, "SHR">;   def : PatGprGpr<srl, SHR>;
def SHRA  : ArithmRR<0x0, "SHRA">;  def : PatGprGpr<sra, SHRA>;
def SHLI  : ArithmRR<0x0, "SHLi">;  def : PatGprImm<shl, SHLI, simm16>;
def SHRI  : ArithmRR<0x0, "SHRi">;  def : PatGprImm<srl, SHRI, simm16>;
def SHRAI : ArithmRR<0x0, "SHRAi">; def : PatGprImm<sra, SHRAI, simm16>;
