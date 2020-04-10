#!/usr/bin/env python3

bestResult = None
bestScore = 0
for line in open('4.txt', 'r'):
    buf = bytes.fromhex(line.rstrip())
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
print(bestResult.decode())
