#!/usr/bin/env python3
import sys
import itertools

lines = sys.stdin.read().splitlines()

class Amp:
    def __init__(self):
        self.prog=[int(x) for x in lines[0].split(',')]
        self.pc=0

    def run(self, inp):
        while 1:
            opcode = self.prog[self.pc] % 100
            imm = self.prog[self.pc:self.pc+4]
            isimm1 = (self.prog[self.pc]//100)%10
            isimm2 = (self.prog[self.pc]//1000)%10
            isimm3 = (self.prog[self.pc]//10000)%10
            def val1(): return imm[1] if isimm1 else self.prog[imm[1]]
            def val2(): return imm[2] if isimm2 else self.prog[imm[2]]
            def val3(): return imm[3] if isimm3 else self.prog[imm[3]]
            if opcode==99:
                return None
            elif opcode==1:
                self.prog[imm[3]] = val1() + val2()
                self.pc += 4
            elif opcode==2:
                self.prog[imm[3]] = val1() * val2()
                self.pc += 4
            elif opcode==3:
                self.prog[imm[1]] = inp.pop(0)
                self.pc += 2
            elif opcode==4:
                return val1()
                self.pc += 2
            elif opcode==5:
                self.pc = val2() if val1() else self.pc+3
            elif opcode==6:
                self.pc = val2() if not val1() else self.pc+3
            elif opcode==7:
                self.prog[imm[3]] = int(val1() < val2())
                self.pc += 4
            elif opcode==8:
                self.prog[imm[3]] = int(val1() == val2())
                self.pc += 4

def get_output_signal(phases):
    signal=0
    for phase in phases:
        signal = Amp().run([phase, signal])
    return signal

def best_output():
    return max(get_output_signal(phases)
            for phases in itertools.permutations([0,1,2,3,4]))

print(best_output())

def get_output_signal(phases):
    signal=0
    amps = [Amp() for _ in range(5)]
    for amp, phase in zip(amps, phases):
        signal = amp.run([phase, signal])
    while True:
        ret = signal
        for amp in amps:
            signal = amp.run([signal])
            if signal is None:
                return ret

def best_output():
    return max(get_output_signal(phases)
            for phases in itertools.permutations([5,6,7,8,9]))

print(best_output())
