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
    inp += base64.b64decode('Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK')
    return encryptECB(key, inp)

def detectECB(inp, blocksize):
    blocks = [inp[i:i+blocksize] for i in range(0, len(inp), blocksize)]
    return len(blocks) != len(set(blocks))

key = randomBytes(16)
for bs in range(2, 100):
    if detectECB(encryption_oracle(b'a'*bs*2), bs):
        break
print('block size detected:', bs)

def makeDictionary(inp):
    myDict = {}
    for i in range(0, 128):
        block = inp + bytes([i])
        encryptedBlock = encryption_oracle(block)[skip:skip+bs]
        myDict[encryptedBlock] = bytes([i])
    return myDict

plain = bytearray()
for i in range(999):
    skip = (i//bs)*bs
    myDict = makeDictionary((b'a'*(bs-1-i%bs) + plain))
    ciphertext = encryption_oracle(b'a'*(bs-1-i%bs))
    block = ciphertext[skip:skip+bs]
    if not block in myDict:
        break
    plain += myDict[block]
print(plain.decode())
