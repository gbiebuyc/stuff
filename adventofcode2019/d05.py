#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()
def run(inp):
    prog=[int(x) for x in lines[0].split(',')]
    pc=0
    while 1:
        opcode = prog[pc] % 100
        imm = prog[pc:pc+4]
        isimm1 = (prog[pc]//100)%10
        isimm2 = (prog[pc]//1000)%10
        isimm3 = (prog[pc]//10000)%10
        def val1(): return imm[1] if isimm1 else prog[imm[1]]
        def val2(): return imm[2] if isimm2 else prog[imm[2]]
        def val3(): return imm[3] if isimm3 else prog[imm[3]]
        if opcode==99:
            break
        elif opcode==1:
            prog[imm[3]] = val1() + val2()
            pc += 4
        elif opcode==2:
            prog[imm[3]] = val1() * val2()
            pc += 4
        elif opcode==3:
            prog[imm[1]] = inp
            pc += 2
        elif opcode==4:
            print(val1())
            pc += 2
        elif opcode==5:
            pc = val2() if val1() else pc+3
        elif opcode==6:
            pc = val2() if not val1() else pc+3
        elif opcode==7:
            prog[imm[3]] = int(val1() < val2())
            pc += 4
        elif opcode==8:
            prog[imm[3]] = int(val1() == val2())
            pc += 4
        
run(1)
run(5)
