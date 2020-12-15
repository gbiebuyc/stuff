#!/usr/bin/env python3
import sys
import math

lines = sys.stdin.read().splitlines()
visited={}
x, y = 0, 0
steps=0
for a in lines[0].split(','):
    d, val = a[0], int(a[1:])
    for _ in range(val):
        x += (0, 0, -1, 1)['UDLR'.index(d)]
        y += (-1, 1, 0, 0)['UDLR'.index(d)]
        steps+=1
        visited[(x, y)]=steps
x, y = 0, 0
steps=0
bestManhattan=math.inf
bestSteps=math.inf
for a in lines[1].split(','):
    d, val = a[0], int(a[1:])
    for _ in range(val):
        x += (0, 0, -1, 1)['UDLR'.index(d)]
        y += (-1, 1, 0, 0)['UDLR'.index(d)]
        steps+=1
        if (x, y) in visited:
            bestManhattan = min(bestManhattan, abs(x)+abs(y))
            bestSteps = min(bestSteps, visited[(x, y)]+steps)
print(bestManhattan)
print(bestSteps)

