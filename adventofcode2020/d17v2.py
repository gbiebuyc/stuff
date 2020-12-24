#!/usr/bin/env python3
from sys import stdin

cubes=set()
for y, l in enumerate(stdin):
    for x, c in enumerate(l):
        if c == '#':
            cubes.add((x, y, 0, 0))

def solve(ispart2, cubes):
    cubes = cubes.copy()
    for _ in range(6):
        newcubes = set()
        for x in range(-6, 14):
            for y in range(-6, 14):
                for z in range(-6, 14):
                    for w in range(-6, 14) if ispart2 else range(1):
                        n = 0
                        for dx in (-1, 0, 1):
                            for dy in (-1, 0, 1):
                                for dz in (-1, 0, 1):
                                    for dw in (-1, 0, 1):
                                        if dx!=0 or dy!=0 or dz!=0 or dw!=0:
                                            if (x+dx, y+dy, z+dz, w+dw) in cubes:
                                                n += 1
                        if (x, y, z, w) in cubes and n in (2, 3):
                            newcubes.add((x, y, z, w))
                        if (x, y, z, w) not in cubes and n==3:
                            newcubes.add((x, y, z, w))
        cubes = newcubes
    print(len(cubes))

solve(False, cubes)
solve(True, cubes)

