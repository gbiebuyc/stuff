#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()

def run(noun, verb):
    prog=[int(x) for x in lines[0].split(',')]
    prog[1]=noun
    prog[2]=verb
    pc=0
    while 1:
        if prog[pc]>2:
            break
        elif prog[pc]==1:
            prog[prog[pc+3]]=prog[prog[pc+2]]+prog[prog[pc+1]]
        elif prog[pc]==2:
            prog[prog[pc+3]]=prog[prog[pc+2]]*prog[prog[pc+1]]
        pc+=4
    return prog[0]

def p1():
    return run(12, 2)

def p2():
    for noun in range(100):
        for verb in range(100):
            if run(noun, verb)==19690720:
                return 100*noun+verb

print(p1())
print(p2())
