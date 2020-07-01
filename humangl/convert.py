#!/usr/bin/env python3
import argparse, sys

# This script converts .bvh file(s) into a single cpp header for HumanGL.
# I got animations from Mixamo.com and used Blender to convert to bvh.

files = sys.argv[1:]
outfile = open('motion.hpp', 'w')
print('vector<vector<vector<float>>> animations{', file=outfile)
for f in files:
    print('{', file=outfile)
    lines = open(f, 'r').readlines()
    i_line = 0
    while not 'MOTION' in lines[i_line]:
        i_line += 1
    lines = lines[i_line+3:]
    for line in lines:
        numbers = line.split()
        nodes = [numbers[i:i+6] for i in range(0, len(numbers), 6)]
        data = []
        data += nodes[0] # Hips pos and rot
        data += nodes[5][3:] # Head
        data += nodes[10][3:] # Left upper arm
        data += nodes[11][3:] # Left lower arm
        data += nodes[34][3:] # Right upper arm
        data += nodes[35][3:] # Right lower arm
        data += nodes[57][3:] # Left upper leg
        data += nodes[58][3:] # Left lower leg
        data += nodes[62][3:] # Right upper leg
        data += nodes[63][3:] # Right lower leg
        print('{', ', '.join(data), '},', file=outfile)
    print('},', file=outfile)
print('};', file=outfile)
