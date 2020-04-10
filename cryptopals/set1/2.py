#!/usr/bin/env python3

def my_xor_function(buf1, buf2):
    buf1 = bytes.fromhex(buf1)
    buf2 = bytes.fromhex(buf2)
    result = bytearray(len(buf1))
    for i in range(len(buf1)):
        result[i] = buf1[i] ^ buf2[i]
    return result.hex()

print(my_xor_function('1c0111001f010100061a024b53535009181c', '686974207468652062756c6c277320657965'))
