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

def encryption_oracle(inp):
    inp += base64.b64decode('Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK')
    return encryptECB(key, inp)

def detectECB(inp, blocksize):
    blocks = [inp[i:i+blocksize] for i in range(0, len(inp), blocksize)]
    return len(blocks) != len(set(blocks))

def profile_for(email):
    if type(email) == str:
        email = email.encode()
    if b'&' in email or b'=' in email:
        raise ValueError('invalid characters in email')
    profile = b'email=' + email + b'&uid=10&role=user'
    return encryptECB(key, profile)

def dec_profile(profile):
    out = {}
    profile = decryptECB(key, profile).decode()
    for entry in profile.split('&'):
        k, v = entry.split('=')
        out[k] = v
    return out

key = randomBytes(16)
email_len = 16 - len('email=&uid=10&role=') % 16
ciphertext1 = profile_for(email_len*'a')
ciphertext2 = profile_for((16-len('email='))*b'a' + b'admin' + b'\x0b'*0xb)
payload = ciphertext1[:-16] + ciphertext2[16:32]
print(dec_profile(payload))
