#!/usr/bin/env python3

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

print(padPKCS7(b"YELLOW SUBMARINE", 20))
print(unpadPKCS7(padPKCS7(b"YELLOW SUBMARINE", 16), 16))
