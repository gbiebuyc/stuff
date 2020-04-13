#!/usr/bin/env python3

def xor(buf1, buf2):
    if len(buf1) != len(buf2):
        raise ValueError('buffers have different lengths')
    return bytes(x ^ y for x, y in zip(buf1, buf2))

buf1 = bytes.fromhex('1c0111001f010100061a024b53535009181c')
buf2 = bytes.fromhex('686974207468652062756c6c277320657965')
print(xor(buf1, buf2).hex())
