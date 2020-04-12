#!/usr/bin/env python3

def padding(blocksize, plaintext):
    n = (blocksize - len(plaintext) % blocksize) % blocksize
    plaintext += bytes([n] * n)
    return plaintext

print(padding(20, b"YELLOW SUBMARINE"))
