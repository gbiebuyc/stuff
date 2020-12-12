#!/usr/bin/env python3
import requests
from sys import argv
from aoc_cookie import AOC_COOKIE

YEAR=2020
DAY=12
INPUT_FILE = 'input-%02d.txt' % DAY
EXAMPLE_FILE = 'input-%02d-example.txt' % DAY
SUBMIT = 's' in argv[1:]
try:
    data = open(INPUT_FILE).read()
except:
    print('Downloading input...')
    r = requests.get(f'https://adventofcode.com/{YEAR}/day/{DAY}/input', cookies={'session': AOC_COOKIE})
    r.raise_for_status()
    data = r.text
    open(INPUT_FILE, 'w').write(data)
try:
    example = open(EXAMPLE_FILE).read()
except:
    print('Downloading example...')
    r = requests.get(f'https://adventofcode.com/{YEAR}/day/{DAY}', cookies={'session': AOC_COOKIE})
    r.raise_for_status()
    example = r.text.split('<pre><code>')[1].split('</code></pre>')[0]
    open(EXAMPLE_FILE, 'w').write(example)


def submit(ans):
    r = requests.get(f'https://adventofcode.com/{YEAR}/day/{DAY}', cookies={'session': AOC_COOKIE})
    if '<input type="hidden" name="level" value="' in r.text:
        lvl = r.text.split('<input type="hidden" name="level" value="')[1].split('"/>')[0]
    else:
        print('Nothing to submit')
        return
    print(f'Submitting part {lvl}...')
    r = requests.post(f'https://adventofcode.com/{YEAR}/day/{DAY}/answer', cookies={'session': AOC_COOKIE}, data={'level': str(lvl), 'answer': str(ans)})
    print(r.text.split('<article><p>')[1].split('</p></article>')[0])

def answer(ans):
    if SUBMIT:
        submit(ans)
    else:
        print(ans)

data = data if SUBMIT else example
lines = data.splitlines()
try:
    nums = [int(n) for n in lines]
    L = len(nums)
except:
    pass



