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
path={}
cur='YOU'
i=0
while cur!='COM':
    path[cur]=i
    cur = connections[cur]
    i += 1
cur='SAN'
i=0
while cur!='COM':
    if cur in path:
        print(i + path[cur] - 2)
        break
    cur = connections[cur]
    i += 1
