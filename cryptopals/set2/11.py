#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES
import random

def xor(buf1, buf2):
    if len(buf1) != len(buf2):
        raise ValueError('buffers have different lengths')
    return bytes(x ^ y for x, y in zip(buf1, buf2))

def padPKCS7(data, blocksize):
    n = blocksize - len(data) % blocksize
    return data + bytes([n] * n)

def unpadPKCS7(data, blocksize):
    if len(data) % blocksize:
        raise ValueError('Input data is not padded')
    n = data[-1]
    if n == 0 or n > blocksize:
        raise ValueError('Padding is incorrect.')
    if data[-n:] != bytes([n] * n):
        raise ValueError("PKCS#7 padding is incorrect.")
    return data[:-n]

def decryptCBC(key, iv, inp):
    out = bytearray(len(inp))
    cipher = AES.new(key, AES.MODE_ECB)
    previous = iv
    for i in range(0, len(inp), 16):
        out[i:i+16] = xor(previous, cipher.decrypt(inp[i:i+16]))
        previous = inp[i:i+16]
    return unpadPKCS7(out, 16)

def encryptCBC(key, iv, inp):
    inp = padPKCS7(inp, 16)
    out = bytearray(len(inp))
    cipher = AES.new(key, AES.MODE_ECB)
    previous = iv
    for i in range(0, len(inp), 16):
        out[i:i+16] = cipher.encrypt(xor(previous, inp[i:i+16]))
        previous = out[i:i+16]
    return out

def encryptECB(key, inp):
    inp = padPKCS7(inp, 16)
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
    inp = bytes(inp)
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
