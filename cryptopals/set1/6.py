#!/usr/bin/env python3
import base64

def hamming_distance(s1, s2):
    result = 0
    for i in range(len(s1)):
        n = s1[i]
        m = s2[i]
        for shift in range(8):
            if ((n >> shift) & 1) != ((m >> shift) & 1):
                result += 1
    return result

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
    result = bytearray(len(data))
    for i in range(len(data)):
        result[i] = data[i] ^ key[i % len(key)]
    return result

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
