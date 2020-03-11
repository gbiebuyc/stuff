#!/usr/bin/env python3
from base64 import b64decode, b64encode

VALID_H = "3F34564B0A1FB3AFE3676911FF990B3127BEC0C2"
SIGNATURE_SIZE = 256
ASN = b"0!0\t\x06\x05+\x0e\x03\x02\x1a\x05\x00\x04\x14"


# https://stackoverflow.com/questions/356090/how-to-compute-the-nth-root-of-a-very-big-integer
def find_invpow(x,n):
    """Finds the integer component of the n'th root of x,
    an integer such that y ** n <= x < (y + 1) ** n.
    """
    high = 1
    while high ** n < x:
        high *= 2
    low = high//2
    while low < high:
        mid = (low + high) // 2
        if low < mid and mid**n < x:
            low = mid
        elif high > mid and mid**n > x:
            high = mid
        else:
            return mid
    return mid + 1

def solve():
    i = 0
    a = b"\x00\x01"
    a += b"\x00"
    a += ASN
    a += bytes.fromhex(VALID_H)
    a += b'\x00' * (SIGNATURE_SIZE - len(a))
    x = int.from_bytes(a, 'big')
    y = find_invpow(x, 3) + 1
    y = y.to_bytes(SIGNATURE_SIZE, byteorder='big')
    y = b64encode(y)
    print(y)

solve()
