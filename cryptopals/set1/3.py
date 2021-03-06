#!/usr/bin/env python3

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

hexStr = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
result = solveSingleCharXOR(bytes.fromhex(hexStr))
print(result.decode())
