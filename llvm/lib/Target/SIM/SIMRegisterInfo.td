//===-- SIMRegisterInfo.td - SIM Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the RISC-W register file
//===----------------------------------------------------------------------===//

let Namespace = "SIM" in {
class SIMReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}
} // end Namespace

def R0  : SIMReg<0, "r0", []>, DwarfRegNum<[0]>;
def R1  : SIMReg<1, "r1", []>, DwarfRegNum<[1]>;
def R2  : SIMReg<2, "r2", []>, DwarfRegNum<[2]>;
def R3  : SIMReg<3, "r3", []>, DwarfRegNum<[3]>;
def R4  : SIMReg<4, "r4", []>, DwarfRegNum<[4]>;
def R5  : SIMReg<5, "r5", []>, DwarfRegNum<[5]>;
def R6  : SIMReg<6, "r6", []>, DwarfRegNum<[6]>;
def R7  : SIMReg<7, "r7", []>, DwarfRegNum<[7]>;
def R8  : SIMReg<8, "r8", []>, DwarfRegNum<[8]>;
def R9  : SIMReg<9, "r9", []>, DwarfRegNum<[9]>;
def R10 : SIMReg<10,"r10", []>, DwarfRegNum<[10]>;
def R11 : SIMReg<11,"r11", []>, DwarfRegNum<[11]>;
def R12 : SIMReg<12,"r12", []>, DwarfRegNum<[12]>;
def R13 : SIMReg<13,"r13", []>, DwarfRegNum<[13]>;
def R14 : SIMReg<14,"r14", []>, DwarfRegNum<[14]>;
def R15 : SIMReg<15,"r15", []>, DwarfRegNum<[15]>;

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def GPR : RegisterClass<"SIM", [i32], 32, (add
    (sequence "R%u", 0, 15)
  )>;

def SP : RegisterClass<"SIM", [i32], 32, (add R2)>;
