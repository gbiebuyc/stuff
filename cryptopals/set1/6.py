#!/usr/bin/env python3
import base64

def hamming_distance(s1, s2):
    return sum(bin(x ^ y).count('1') for x, y in zip(s1, s2))

def solveSingleCharXOR(buf):
    bestResult = None
    bestScore = 0
    for i in range(256):
        result = bytearray(len(buf))
        score = 0
        for j in range(len(buf)):
            result[j] = buf[j] ^ i
            if chr(result[j]).upper() in 'ETAOIN SHRDLU':
                score += 1;
        if score > bestScore:
            bestScore = score
            bestResult = result
    return bestResult

def find_key(data, keysize):
    key = bytearray(keysize)
    for i in range(keysize):
        block = [data[j] for j in range(i, len(data), keysize)]
        plain = solveSingleCharXOR(block)
        key[i] = block[0] ^ plain[0]
    return key

def solveRepeatingKeyXOR(data, key):
    return bytes(x ^ key[i % len(key)] for i, x in enumerate(data))

data = base64.b64decode(open('6.txt', 'r').read())
keysizes = []
for keysize in range(2, 41):
    dist = hamming_distance(data[:keysize], data[keysize:2*keysize])
    dist /= keysize #normalize
    keysizes.append((keysize, dist))
keysizes = [x for x, y in sorted(keysizes, key=lambda e: e[1])]
# keysizes = sorted(keysizes, key=lambda e: e[1])
# print(keysizes)
# raise SystemExit
# for keysize in keysizes:
#     key = find_key(data, keysize)
#     plain = solveRepeatingKeyXOR(data, key)
#     # print(plain)
#     print(key)
print(solveRepeatingKeyXOR(data, b'Terminator X: Bring the noise').decode())
