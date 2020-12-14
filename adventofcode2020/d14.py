#!/usr/bin/env python3
import requests
import math
from sys import argv
from aoc_cookie import AOC_COOKIE

YEAR, DAY = 2020, 13
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
