#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()
connections={}
for l in lines:
    a, b = l.split(')')
    connections[b] = a

def f(x):
    if x=='COM':
        return 0
    return 1 + f(connections[x])

print(sum(f(x) for x in connections))

# PART 2
path=[]
cur='YOU'
while cur!='COM':
    path.append(cur)
    cur = connections[cur]
cur='SAN'
i=0
while cur!='COM':
    for j, other in enumerate(path):
        if other==cur:
            print(i+j-2)
            exit(0)
    cur = connections[cur]
    i += 1

