#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()
print(sum([int(mass)//3-2 for mass in lines]))

def f(mass):
    ret=mass//3-2
    if ret<0:
        return 0
    return ret+f(ret)
print(sum([f(int(mass)) for mass in lines]))
