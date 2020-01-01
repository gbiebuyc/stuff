#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
    print('Need a file as argument')
    sys.exit(1)

size = 0
data = open(sys.argv[1], mode='rb').read(510)
for count, byte in enumerate(data, start=1):
    if byte: size = count

print('Size: %s of 510 bytes' % size)
print('Used: %.2f%%' % (size/5.10))
