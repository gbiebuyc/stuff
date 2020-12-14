#!/usr/bin/env python3
import requests
import math
from sys import argv
from aoc_cookie import AOC_COOKIE

YEAR, DAY = 2020, 14
INPUT_FILE = 'input-%02d.txt' % DAY
EXAMPLE_FILE = 'input-%02d-example.txt' % DAY
try:
    full_data = open(INPUT_FILE).read()
except:
    print('Downloading input...')
    r = requests.get(f'https://adventofcode.com/{YEAR}/day/{DAY}/input', cookies={'session': AOC_COOKIE})
    r.raise_for_status()
    full_data = r.text
    open(INPUT_FILE, 'w').write(full_data)
try:
    example = open(EXAMPLE_FILE).read()
except:
    print('Downloading example...')
    r = requests.get(f'https://adventofcode.com/{YEAR}/day/{DAY}', cookies={'session': AOC_COOKIE})
    r.raise_for_status()
    example = r.text.split('<pre><code>')[1].split('</code></pre>')[0]
    open(EXAMPLE_FILE, 'w').write(example)

data = full_data if 'f' in argv[1:] else example
lines = data.splitlines()

# PART 1
mask=None
mem={}
for l in lines:
    if 'mask' in l:
        mask=l.split()[2]
    else:
        addr = int(l.split('[')[1].split(']')[0])
        val = int(l.split()[2])
        for i in range(36):
            if mask[i]=='0':
                val &= ~(1<<(36-1-i))
            elif mask[i]=='1':
                val |= (1<<(36-1-i))
        mem[addr]=val
print(sum(mem.values()))


# PART 2
mask=None
mem={}
for l in lines:
    if 'mask' in l:
        mask=l.split()[2]
    else:
        addr = int(l.split('[')[1].split(']')[0])
        val = int(l.split()[2])
        for i in range(36):
            if mask[i]=='1':
                addr |= (1<<(36-1-i))
        for i in range(2**mask.count('X')):
            j=0
            a=addr
            for k in range(36):
                if mask[k]=='X':
                    if (i>>j)&1:
                        a &= ~(1<<(36-1-k))
                    else:
                        a |= (1<<(36-1-k))
                    j+=1
            mem[a]=val
print(sum(mem.values()))
