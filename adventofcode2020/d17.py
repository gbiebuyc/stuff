#!/usr/bin/env python3
import sys
import copy

lines = sys.stdin.read().splitlines()
W, H = len(lines[0])+12, len(lines)+12
state=[[['.']*W for _ in range(H)] for _ in range(13)]
for y in range(len(lines)):
    for x in range(len(lines[0])):
        state[6][y+6][x+6] = lines[y][x]
def isInside(x, y, z):
    return x>=0 and y>=0 and z>=0 and x<W and y<H and z<13

def countActiveNeighbors(x, y, z, state):
    count=0
    for dz in (-1, 0, 1):
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                if dz==0 and dy==0 and dx==0:
                    continue
                if not isInside(x+dx, y+dy, z+dz):
                    continue
                if state[z+dz][y+dy][x+dx]=='#':
                    count += 1
    return count

for _ in range(6):
    newstate = copy.deepcopy(state)
    for z in range(13):
        for y in range(H):
            for x in range(W):
                n = countActiveNeighbors(x, y, z, state)
                if state[z][y][x]=='#':
                    if not (n==2 or n==3):
                        newstate[z][y][x] = '.'
                elif state[z][y][x]=='.':
                    if n==3:
                        newstate[z][y][x] = '#'
    state = newstate

print(str(state).count('#'))


# PART 2
W, H = len(lines[0])+12, len(lines)+12
state=[[[['.']*W for _ in range(H)] for _ in range(13)] for _ in range(13)]
for y in range(len(lines)):
    for x in range(len(lines[0])):
        state[6][6][y+6][x+6] = lines[y][x]
def isInside(x, y, z, w):
    return x>=0 and y>=0 and z>=0 and w>=0 and x<W and y<H and z<13 and w<13

def countActiveNeighbors(x, y, z, w, state):
    count=0
    for dw in (-1, 0, 1):
        for dz in (-1, 0, 1):
            for dy in (-1, 0, 1):
                for dx in (-1, 0, 1):
                    if dw==0 and dz==0 and dy==0 and dx==0:
                        continue
                    if not isInside(x+dx, y+dy, z+dz, w+dw):
                        continue
                    if state[w+dw][z+dz][y+dy][x+dx]=='#':
                        count += 1
    return count

for _ in range(6):
    newstate = copy.deepcopy(state)
    for w in range(13):
        for z in range(13):
            for y in range(H):
                for x in range(W):
                    n = countActiveNeighbors(x, y, z, w, state)
                    if state[w][z][y][x]=='#':
                        if not (n==2 or n==3):
                            newstate[w][z][y][x] = '.'
                    elif state[w][z][y][x]=='.':
                        if n==3:
                            newstate[w][z][y][x] = '#'
    state = newstate

print(str(state).count('#'))
