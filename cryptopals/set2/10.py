#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES

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
    return out

# test decrypt
ciphertext = base64.b64decode(open('10.txt', 'r').read())
key = b'YELLOW SUBMARINE'
iv = bytes([0] * 16)
plaintext = decryptCBC(key, iv, ciphertext)
print(plaintext.decode())

# test decrypt & encrypt
plaintext = b'hello world bruh'
assert decryptCBC(key, iv, encryptCBC(key, iv, plaintext)) == plaintext
