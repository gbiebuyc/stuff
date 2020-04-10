#!/usr/bin/env python3

plaintext = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal".encode()
key = 'ICE'.encode()
cyphertext = bytearray(len(plaintext))
for i in range(len(plaintext)):
    cyphertext[i] = plaintext[i] ^ key[i % len(key)]
print(cyphertext.hex())
