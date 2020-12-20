#!/usr/bin/env python3
from sys import stdin
import itertools
import math

tiles={}
for tile in stdin.read().strip().split('\n\n'):
    tiles[int(tile[5:9])] = tile.splitlines()[1:]

def check(border, other):
    other_top = other[0]
    other_bottom = other[-1]
    other_left = ''.join(row[0] for row in other)
    other_right = ''.join(row[-1] for row in other)
    return border in (other_top, other_top[::-1],
                      other_bottom, other_bottom[::-1],
                      other_left, other_left[::-1],
                      other_right, other_right[::-1])

corners=[]
for cur in tiles:
    borders = [0,0,0,0]
    for other in tiles:
        if cur == other:
            continue
        top = tiles[cur][0]
        bottom = tiles[cur][-1]
        left = ''.join(row[0] for row in tiles[cur])
        right = ''.join(row[-1] for row in tiles[cur])
        if check(top, tiles[other]):
            borders[0] = 1
        if check(right, tiles[other]):
            borders[1] = 1
        if check(bottom, tiles[other]):
            borders[2] = 1
        if check(left, tiles[other]):
            borders[3] = 1
    if sum(borders) == 2:
        corners.append(cur)

print(f'corners: {corners}')
print(corners[0] * corners[1] * corners[2] * corners[3])
