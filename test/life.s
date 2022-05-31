	.text
	.file	"life.c"
	.globl	getValue
	.type	getValue,@function
getValue:
	ADDi	r2 r2 -44
	STi	r1 r2 40
	STi	r3 r2 36
	ADDi	r3 r2 44
	STi	r9 r3 -12
	STi	r10 r3 -16
	STi	r11 r3 -20
	LDi	r4 r3 -12
	LDi	r9 r3 -20
	SHLi	r9 r9 3
	ADD	r4 r4 r9
	LDi	r9 r3 -16
	SHRAi	r10 r9 31
	SHRi	r10 r10 27
	ADD	r9 r9 r10
	SHRAi	r9 r9 5
	ADD	r4 r4 r9
	STi	r4 r3 -24
	LDi	r4 r3 -16
	SHRAi	r9 r4 31
	SHRi	r9 r9 27
	ADD	r9 r4 r9
	ANDi	r9 r9 -32
	SUB	r4 r4 r9
	STi	r4 r3 -28
	LDi	r4 r3 -28
	MOVli	r10 1
	SHL	r4 r10 r4
	STi	r4 r3 -32
	LDi	r4 r3 -24
	LDi	r4 r4 0
	LDi	r9 r3 -32
	AND	r4 r4 r9
	MOVli	r9 0
	STi	r9 r3 -44
	STi	r10 r3 -40
	B.NE	r4 r9 .LBB0_2
	LDi	r4 r3 -44
	STi	r4 r3 -40
.LBB0_2:
	LDi	r4 r3 -40
	ANDi	r4 r4 1
	STi	r4 r3 -36
	LDi	r9 r3 -36
	LDi	r3 r2 36
	LDi	r1 r2 40
	ADDi	r2 r2 44
	BR	r1
.Lfunc_end0:
	.size	getValue, .Lfunc_end0-getValue

	.globl	setValue
	.type	setValue,@function
setValue:
	ADDi	r2 r2 -44
	STi	r1 r2 40
	STi	r3 r2 36
	ADDi	r3 r2 44
	STi	r9 r3 -12
	STi	r10 r3 -16
	STi	r11 r3 -20
	STi	r12 r3 -24
	LDi	r4 r3 -12
	LDi	r9 r3 -20
	SHLi	r9 r9 3
	ADD	r4 r4 r9
	LDi	r9 r3 -16
	SHRAi	r10 r9 31
	SHRi	r10 r10 27
	ADD	r9 r9 r10
	SHRAi	r9 r9 5
	ADD	r4 r4 r9
	STi	r4 r3 -28
	LDi	r4 r3 -16
	SHRAi	r9 r4 31
	SHRi	r9 r9 27
	ADD	r9 r4 r9
	ANDi	r9 r9 -32
	SUB	r4 r4 r9
	STi	r4 r3 -32
	LDi	r9 r3 -32
	MOVli	r4 1
	SHL	r4 r4 r9
	STi	r4 r3 -36
	LDi	r4 r3 -24
	MOVli	r9 0
	B.EQ	r4 r9 .LBB1_2
	B	.LBB1_1
.LBB1_1:
	LDi	r4 r3 -28
	LDi	r4 r4 0
	LDi	r9 r3 -36
	OR	r4 r4 r9
	STi	r4 r3 -40
	LDi	r4 r3 -40
	LDi	r9 r3 -28
	STi	r4 r9 0
	B	.LBB1_3
.LBB1_2:
	LDi	r4 r3 -28
	LDi	r4 r4 0
	LDi	r9 r3 -36
	XORi	r9 r9 -1
	AND	r4 r4 r9
	STi	r4 r3 -44
	LDi	r4 r3 -44
	LDi	r9 r3 -28
	STi	r4 r9 0
	B	.LBB1_3
.LBB1_3:
	LDi	r3 r2 36
	LDi	r1 r2 40
	ADDi	r2 r2 44
	BR	r1
.Lfunc_end1:
	.size	setValue, .Lfunc_end1-setValue

	.globl	main
	.type	main,@function
main:
	ADDi	r2 r2 -120
	STi	r1 r2 116
	STi	r3 r2 112
	ADDi	r3 r2 120
	MOVli	r4 0
	STi	r4 r3 -12
	MOVli	r9 31744
	STi	r9 r3 -16
	MOVli	r9 30720
	STi	r9 r3 -20
	STi	r4 r3 -24
	B	.LBB2_1
.LBB2_1:
	LDi	r4 r3 -24
	MOVli	r9 127
	B.GT	r4 r9 .LBB2_8
	B	.LBB2_2
.LBB2_2:
	MOVli	r4 0
	STi	r4 r3 -28
	B	.LBB2_3
.LBB2_3:
	LDi	r4 r3 -28
	MOVli	r9 7
	B.GT	r4 r9 .LBB2_6
	B	.LBB2_4
.LBB2_4:
	BL	r1 __rand
	LDi	r4 r3 -20
	LDi	r10 r3 -24
	SHLi	r10 r10 8
	SHRAi	r10 r10 5
	ADD	r4 r4 r10
	LDi	r10 r3 -28
	ADD	r4 r4 r10
	STi	r9 r4 0
	B	.LBB2_5
.LBB2_5:
	LDi	r4 r3 -28
	ADDi	r4 r4 1
	STi	r4 r3 -28
	B	.LBB2_3
.LBB2_6:
	B	.LBB2_7
.LBB2_7:
	LDi	r4 r3 -24
	ADDi	r4 r4 1
	STi	r4 r3 -24
	B	.LBB2_1
.LBB2_8:
	B	.LBB2_9
.LBB2_9:
	MOVli	r4 0
	STi	r4 r3 -32
	B	.LBB2_10
.LBB2_10:
	LDi	r4 r3 -32
	MOVli	r9 127
	B.GT	r4 r9 .LBB2_28
	B	.LBB2_11
.LBB2_11:
	MOVli	r4 0
	STi	r4 r3 -36
	B	.LBB2_12
.LBB2_12:
	LDi	r4 r3 -36
	MOVli	r9 255
	B.GT	r4 r9 .LBB2_26
	B	.LBB2_13
.LBB2_13:
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 -1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 -1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	STi	r9 r3 -100
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 -1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	ADDi	r4 r9 0
	LDi	r9 r3 -100
	ADD	r4 r9 r4
	STi	r4 r3 -96
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 -1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -96
	ADD	r4 r4 r9
	STi	r4 r3 -92
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 -1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -92
	ADD	r4 r4 r9
	STi	r4 r3 -88
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -88
	ADD	r4 r4 r9
	STi	r4 r3 -84
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 -1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -84
	ADD	r4 r4 r9
	STi	r4 r3 -80
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -80
	ADD	r4 r4 r9
	STi	r4 r3 -76
	LDi	r9 r3 -20
	LDi	r4 r3 -36
	ADDi	r4 r4 1
	SHRAi	r10 r4 31
	SHRi	r10 r10 24
	ADD	r10 r4 r10
	ANDi	r10 r10 -256
	SUB	r10 r4 r10
	LDi	r4 r3 -32
	ADDi	r4 r4 1
	SHRAi	r11 r4 31
	SHRi	r11 r11 25
	ADD	r11 r4 r11
	ANDi	r11 r11 -128
	SUB	r11 r4 r11
	BL	r1 getValue
	LDi	r4 r3 -76
	ADD	r4 r4 r9
	STi	r4 r3 -40
	LDi	r9 r3 -20
	LDi	r10 r3 -36
	LDi	r11 r3 -32
	BL	r1 getValue
	STi	r9 r3 -44
	LDi	r4 r3 -44
	MOVli	r9 0
	B.EQ	r4 r9 .LBB2_20
	B	.LBB2_14
.LBB2_14:
	LDi	r4 r3 -40
	MOVli	r10 1
	MOVli	r9 2
	STi	r10 r3 -104
	B.EQ	r4 r9 .LBB2_16
	B	.LBB2_15
.LBB2_15:
	LDi	r4 r3 -40
	MOVli	r9 0
	STi	r9 r3 -112
	MOVli	r10 1
	MOVli	r9 3
	STi	r10 r3 -108
	B.EQ	r4 r9 .LBB2_45
	LDi	r4 r3 -112
	STi	r4 r3 -108
.LBB2_45:
	LDi	r4 r3 -108
	STi	r4 r3 -104
	B	.LBB2_16
.LBB2_16:
	LDi	r4 r3 -104
	ANDi	r4 r4 1
	STi	r4 r3 -48
	LDi	r4 r3 -48
	MOVli	r9 0
	B.EQ	r4 r9 .LBB2_18
	B	.LBB2_17
.LBB2_17:
	LDi	r9 r3 -16
	LDi	r10 r3 -36
	LDi	r11 r3 -32
	MOVli	r12 1
	BL	r1 setValue
	B	.LBB2_19
.LBB2_18:
	LDi	r9 r3 -16
	LDi	r10 r3 -36
	LDi	r11 r3 -32
	MOVli	r12 0
	BL	r1 setValue
	B	.LBB2_19
.LBB2_19:
	B	.LBB2_24
.LBB2_20:
	LDi	r4 r3 -40
	MOVli	r9 0
	STi	r9 r3 -120
	MOVli	r10 1
	MOVli	r9 3
	STi	r10 r3 -116
	B.EQ	r4 r9 .LBB2_47
	LDi	r4 r3 -120
	STi	r4 r3 -116
.LBB2_47:
	LDi	r9 r3 -120
	LDi	r4 r3 -116
	ANDi	r4 r4 1
	STi	r4 r3 -52
	LDi	r4 r3 -52
	B.EQ	r4 r9 .LBB2_22
	B	.LBB2_21
.LBB2_21:
	LDi	r9 r3 -16
	LDi	r10 r3 -36
	LDi	r11 r3 -32
	MOVli	r12 1
	BL	r1 setValue
	B	.LBB2_23
.LBB2_22:
	LDi	r9 r3 -16
	LDi	r10 r3 -36
	LDi	r11 r3 -32
	MOVli	r12 0
	BL	r1 setValue
	B	.LBB2_23
.LBB2_23:
	B	.LBB2_24
.LBB2_24:
	B	.LBB2_25
.LBB2_25:
	LDi	r4 r3 -36
	ADDi	r4 r4 1
	STi	r4 r3 -36
	B	.LBB2_12
.LBB2_26:
	B	.LBB2_27
.LBB2_27:
	LDi	r4 r3 -32
	ADDi	r4 r4 1
	STi	r4 r3 -32
	B	.LBB2_10
.LBB2_28:
	MOVli	r4 0
	STi	r4 r3 -56
	B	.LBB2_29
.LBB2_29:
	LDi	r4 r3 -56
	MOVli	r9 127
	B.GT	r4 r9 .LBB2_39
	B	.LBB2_30
.LBB2_30:
	MOVli	r4 0
	STi	r4 r3 -60
	B	.LBB2_31
.LBB2_31:
	LDi	r4 r3 -60
	MOVli	r9 255
	B.GT	r4 r9 .LBB2_37
	B	.LBB2_32
.LBB2_32:
	LDi	r9 r3 -16
	LDi	r10 r3 -60
	LDi	r11 r3 -56
	BL	r1 getValue
	STi	r9 r3 -64
	LDi	r4 r3 -64
	MOVli	r9 0
	B.EQ	r4 r9 .LBB2_34
	B	.LBB2_33
.LBB2_33:
	LDi	r9 r3 -60
	LDi	r10 r3 -56
	MOVli	r11 -1
	BL	r1 put_pixel
	B	.LBB2_35
.LBB2_34:
	LDi	r9 r3 -60
	LDi	r10 r3 -56
	MOVhi	r4 65280
	ADDi	r11 r4 0
	BL	r1 put_pixel
	B	.LBB2_35
.LBB2_35:
	B	.LBB2_36
.LBB2_36:
	LDi	r4 r3 -60
	ADDi	r4 r4 1
	STi	r4 r3 -60
	B	.LBB2_31
.LBB2_37:
	B	.LBB2_38
.LBB2_38:
	LDi	r4 r3 -56
	ADDi	r4 r4 1
	STi	r4 r3 -56
	B	.LBB2_29
.LBB2_39:
	MOVli	r4 0
	STi	r4 r3 -68
	B	.LBB2_40
.LBB2_40:
	LDi	r4 r3 -68
	MOVli	r9 4
	B.GT	r4 r9 .LBB2_43
	B	.LBB2_41
.LBB2_41:
	BL	r1 __flush
	B	.LBB2_42
.LBB2_42:
	LDi	r4 r3 -68
	ADDi	r4 r4 1
	STi	r4 r3 -68
	B	.LBB2_40
.LBB2_43:
	LDi	r4 r3 -16
	STi	r4 r3 -72
	LDi	r4 r3 -20
	STi	r4 r3 -16
	LDi	r4 r3 -72
	STi	r4 r3 -20
	B	.LBB2_9
.Lfunc_end2:
	.size	main, .Lfunc_end2-main

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
.Lfunc_end3:
	.size	put_pixel, .Lfunc_end3-put_pixel

	.ident	"clang version 12.0.1 (git@github.com:giyakov/llvm-project.git 846ea33a7a159f20fed3c0027b5c638dcab7b25e)"
	.section	".note.GNU-stack","",@progbits
