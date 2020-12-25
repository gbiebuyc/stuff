#!/usr/bin/env python3

CARD_PUB_KEY = 8421034
DOOR_PUB_KEY = 15993936

def calc_loop_size(pub_key):
    val=1
    loop_size=0
    while val != pub_key:
        loop_size += 1
        val *= 7
        val %= 20201227
    return loop_size

def calc_encryption_key(subj_nbr, loop_size):
    val=1
    for _ in range(loop_size):
        val *= subj_nbr
        val %= 20201227
    return val

print(calc_encryption_key(CARD_PUB_KEY, calc_loop_size(DOOR_PUB_KEY)))
