#!/usr/bin/env python3

import sys
import re

if len(sys.argv) != 2:
	sys.exit("wrong args")

sim_runtime = '''
_start:
MOVli r0  0
MOVli r1  0
MOVli r2  0
MOVli r3  0
MOVli r4  0
MOVli r5  0
MOVli r6  0
MOVli r7  0
MOVli r8  0
MOVli r9  0
MOVli r10 0
MOVli r11 0
MOVli r12 0
MOVli r13 0
MOVli r14 0
MOVli r15 0
MOVli r2 24576
BL r1 main
EXIT
__flush:
FLUSH
BR r1
__bkpt:
BKPT
BR r1
__rand:
RAND r9
BR r1
'''
print(sim_runtime)

lines = []
with open(sys.argv[1]) as file:
    lines = file.readlines()
    lines = [line.lstrip().rstrip() for line in lines]

re_comment = re.compile(r"\s*(;.*)?$")
re_label = re.compile(r"^(.?\w*):$")

for l in lines:
	l = re.sub(re_comment, '', l)
	if len(l) == 0:
		continue
	if l[0] == '.':
		m = re.search(re_label, l)
		if not m:
			continue
	l = l.replace("\t", "\t ")
	print(l)