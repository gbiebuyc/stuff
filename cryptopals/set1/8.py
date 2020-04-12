#!/usr/bin/env python3

for i_line, line in enumerate(open('8.txt', 'r')):
    line = line.rstrip()
    blocks = [line[i:i+16] for i in range(0, len(line), 16)]
    if len(blocks) != len(set(blocks)):
        print('line', i_line, 'is ECB')
