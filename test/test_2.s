	.text
	.file	"test_2.c"
	.globl	main
	.type	main,@function
main:
	ADDi	r2 r2 -28
	STi	r1 r2 24
	STi	r3 r2 20
	ADDi	r3 r2 28
	MOVli	r4 0
	STi	r4 r3 -12
	STi	r4 r3 -16
	B	.LBB0_1
.LBB0_1:
	LDi	r4 r3 -16
	MOVli	r9 127
	B.GT	r4 r9 .LBB0_8
	B	.LBB0_2
.LBB0_2:
	MOVli	r4 0
	STi	r4 r3 -20
	B	.LBB0_3
.LBB0_3:
	LDi	r4 r3 -20
	MOVli	r9 255
	B.GT	r4 r9 .LBB0_6
	B	.LBB0_4
.LBB0_4:
	LDi	r4 r3 -20
	STi	r4 r3 -24
	LDi	r4 r3 -16
	STi	r4 r3 -28
	BL	r1 __rand
	LDi	r10 r3 -28
	ADDi	r11 r9 0
	LDi	r9 r3 -24
	BL	r1 put_pixel
	B	.LBB0_5
.LBB0_5:
	LDi	r4 r3 -20
	ADDi	r4 r4 1
	STi	r4 r3 -20
	B	.LBB0_3
.LBB0_6:
	B	.LBB0_7
.LBB0_7:
	LDi	r4 r3 -16
	ADDi	r4 r4 1
	STi	r4 r3 -16
	B	.LBB0_1
.LBB0_8:
	BL	r1 __flush
	MOVli	r9 0
	LDi	r3 r2 20
	LDi	r1 r2 24
	ADDi	r2 r2 28
	BR	r1
.Lfunc_end0:
	.size	main, .Lfunc_end0-main

	.type	put_pixel,@function
put_pixel:
	ADDi	r2 r2 -20
	STi	r1 r2 16
	STi	r3 r2 12
	ADDi	r3 r2 20
	STi	r9 r3 -12
	STi	r10 r3 -16
	STi	r11 r3 -20
	LDi	r4 r3 -20
	LDi	r9 r3 -16
	SHLi	r9 r9 8
	LDi	r10 r3 -12
	ADD	r9 r9 r10
	MOVhi	r10 1
	ADDi	r10 r10 32768
	ADD	r9 r9 r10
	STi	r4 r9 0
	LDi	r3 r2 12
	LDi	r1 r2 16
	ADDi	r2 r2 20
	BR	r1
.Lfunc_end1:
	.size	put_pixel, .Lfunc_end1-put_pixel

	.ident	"clang version 12.0.1 (git@github.com:giyakov/llvm-project.git 05a9009e56c333119a99fabe26769cd1e3aa2a5d)"
	.section	".note.GNU-stack","",@progbits
