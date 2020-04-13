#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES
import random

def xor(buf1, buf2):
    assert len(buf1) == len(buf2)
    return bytes(x ^ y for x, y in zip(buf1, buf2))

def decryptCBC(key, iv, inp):
    out = bytearray(len(inp))
    cipher = AES.new(key, AES.MODE_ECB)
    previous = iv
    for i in range(0, len(inp), 16):
        out[i:i+16] = xor(previous, cipher.decrypt(inp[i:i+16]))
        previous = inp[i:i+16]
    return out

def encryptCBC(key, iv, inp):
    out = bytearray(len(inp))
    cipher = AES.new(key, AES.MODE_ECB)
    previous = iv
    for i in range(0, len(inp), 16):
        out[i:i+16] = cipher.encrypt(xor(previous, inp[i:i+16]))
        previous = out[i:i+16]
    return bytes(out)

def encryptECB(key, inp):
    cipher = AES.new(key, AES.MODE_ECB)
    return cipher.encrypt(inp)

def randomBytes(n):
    return bytes(random.randint(0, 255) for i in range(n))

def encryption_oracle(inp):
    random_key = randomBytes(16)
    random_bytes = randomBytes(random.randint(5, 10))
    random_bytes2 = randomBytes(random.randint(5, 10))
    if random.randint(0, 1) == 1:
        return encryptECB(random_key, inp)
    iv = randomBytes(16)
    return encryptCBC(random_key, iv, inp)

def detectECB(inp):
    blocks = [inp[i:i+16] for i in range(0, len(inp), 16)]
    return len(blocks) != len(set(blocks))

cbc, ecb = 0, 0
for i in range(1000):
    cyphertext = encryption_oracle(b'a' * 16 * 3)
    if detectECB(cyphertext):
        ecb += 1
    else:
        cbc += 1
print(cbc, ecb) # should be relatively close
