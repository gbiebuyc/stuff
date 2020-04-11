#!/usr/bin/env python3

def solveRepeatingKeyXOR(data, key):
    result = bytearray(len(data))
    for i in range(len(data)):
        result[i] = data[i] ^ key[i % len(key)]
    return result

plaintext = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal".encode()
key = 'ICE'.encode()
print(solveRepeatingKeyXOR(plaintext, key).hex())
