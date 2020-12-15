#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()

def solve(n):
    turn=1
    spoken={}
    def addtospoken(x, turn):
        if x in spoken:
            spoken[x][1]=spoken[x][0]
            spoken[x][0]=turn
        else:
            spoken[x]=[turn, -1]

    for x in lines[0].split(','):
        x=int(x)
        addtospoken(x, turn)
        turn+=1
        last=x

    while turn<=n:
        if spoken[last][1]==-1:
            x=0
        else:
            x=spoken[last][0]-spoken[last][1]
        addtospoken(x, turn)
        turn+=1
        last=x
    return last

print(solve(2020))
print(solve(30000000))
