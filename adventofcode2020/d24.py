#!/usr/bin/env python3
from sys import stdin

data = stdin.read()
tiles = set()
for line in data.splitlines():
    x, y = 0, 0
    while len(line):
        if line[:1] == 'e':
            x += 1
            line = line[1:]
        elif line[:2] == 'se':
            x += 0.5
            y += 1
            line = line[2:]
        elif line[:2] == 'sw':
            x -= 0.5
            y += 1
            line = line[2:]
        elif line[:1] == 'w':
            x -= 1
            line = line[1:]
        elif line[:2] == 'nw':
            x -= 0.5
            y -= 1
            line = line[2:]
        elif line[:2] == 'ne':
            x += 0.5
            y -= 1
            line = line[2:]
    if (x, y) in tiles:
        tiles.remove((x, y))
    else:
        tiles.add((x, y))

print(len(tiles))

for _ in range(100):
    newtiles = set()
    for y in range(-100, 100):
        for x in range(-100, 100):
            if y%2:
                x += 0.5
            n=0
            for dx, dy in ((.5,-1), (1,0), (.5,1), (-.5,1), (-1,0), (-.5,-1)):
                if (x+dx, y+dy) in tiles:
                    n += 1
            if (x, y) in tiles and n in (1,2):
                newtiles.add((x, y))
            if (x, y) not in tiles and n==2:
                newtiles.add((x, y))
    tiles = newtiles
print(len(tiles))

