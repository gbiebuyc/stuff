#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES
import random

def xor(buf1, buf2):
    if len(buf1) != len(buf2):
        raise ValueError('buffers have different lengths')
    return bytes(x ^ y for x, y in zip(buf1, buf2))

def padPKCS7(data, blocksize=16):
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

def decryptECB(key, inp):
    cipher = AES.new(key, AES.MODE_ECB)
    inp = cipher.decrypt(inp)
    return unpadPKCS7(inp, 16)

def randomBytes(n):
    return bytes(random.randint(0, 255) for i in range(n))

def the_oracle(userdata):
    if type(userdata) == str:
        userdata = userdata.encode()
    if b';' in userdata or b'=' in userdata:
        raise ValueError('invalid characters in userdata')
    profile = b"comment1=cooking%20MCs;userdata=" + userdata + b";comment2=%20like%20a%20pound%20of%20bacon"
    return encryptCBC(key, iv, profile)

def decrypt_and_check_admin(ct):
    pt = decryptCBC(key, iv, ct)
    print('decrypted:', pt)
    if b';admin=true;' in pt:
        print('SUCCESS')
    else:
        print('FAIL')

key = randomBytes(16)
iv = randomBytes(16)
pad = b'x'*16
ct = the_oracle(pad + pad)
ct[32:48] = xor(ct[32:48], xor(pad, b';admin=true;xxxx'))
decrypt_and_check_admin(ct)
