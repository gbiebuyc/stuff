#!/usr/bin/env python3
import struct
BLOCK_SIZE = 16
UMAX = int(pow(256, BLOCK_SIZE))

with open('body.enc.ppm', 'rb') as f:
    filedata = f.read()
    header = filedata[:16]
    data = bytearray(filedata[16:])

for i in reversed(range(1, 291358)):
    i*=16
    block = int(data[i:i+16].hex(), 16)
    block_prev = int(data[i-16:i].hex(), 16)
    block -= block_prev
    block %= UMAX
    data[i:i+16] = bytes.fromhex(format(block, 'x').rjust(32, '0')).rjust(16, b'\x00')

with open('body.dec.ppm', 'wb') as f:
    f.write(header+data)
