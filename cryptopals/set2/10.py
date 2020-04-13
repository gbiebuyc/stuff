#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES

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

# test decrypt
ciphertext = base64.b64decode(open('10.txt', 'r').read())
key = b'YELLOW SUBMARINE'
iv = bytes([0] * 16)
plaintext = decryptCBC(key, iv, ciphertext)
print(plaintext.decode())

# test decrypt & encrypt
plaintext = b'hello world'
assert decryptCBC(key, iv, encryptCBC(key, iv, plaintext)) == plaintext
