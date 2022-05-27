//=== SIMInstrFormats.td - SIM Instruction Formats -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Describe SIM instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  FF FF FF FF
//        ^^ ^^ - r3_imm - third reg or imm
//      ^       - r2     - second reg
//     ^        - r1     - first reg
//  ^^          - opcode - operation code
//
//===----------------------------------------------------------------------===//

// Generic SIM Format
class SIMInst<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>: Instruction
{
  let Namespace = "SIM";
  let DecoderNamespace = "SIM";
  let Size = 4;

  field bits<32> Inst;

  bits<8>  Opcode = op;
  bits<4>  r1 = 0;
  bits<4>  r2 = 0;
  bits<16> r3_imm = 0;

  let Inst{31-24} = Opcode;
  let Inst{23-20} = r1;
  let Inst{19-16} = r2;
  let Inst{15-0}  = r3_imm;

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString      = asmstr;
  let Pattern        = pattern;
}

// Pseudo instructions format
class SIMPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
   : SIMInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
