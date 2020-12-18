#!/usr/bin/env python3
import sys
import re

lines = sys.stdin.read().splitlines()

def replace(matchobj):
    return str(eval(matchobj.group(0)))

def evaluate(expr):
    while ' ' in expr:
        expr = re.sub(r'\(\d+\)', replace, expr, count=1)
        expr = re.sub(r'\d+ [+*] \d+', replace, expr, count=1)
    return int(expr)

print(sum(evaluate(l) for l in lines))

# PART 2
def evaluate2(expr):
    while ' ' in expr:
        #print(expr)
        old = expr
        expr = re.sub(r'\(\d+ \+ \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\d+ \+ \d+', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+ \* \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+ \* \d+ \* \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+ \* \d+ \* \d+ \* \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+ \* \d+ \* \d+ \* \d+ \* \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+ \* \d+ \* \d+ \* \d+ \* \d+ \* \d+\)', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\d+ \* \d+', replace, expr, count=1)
        if expr != old: continue
        expr = re.sub(r'\(\d+\)', replace, expr, count=1)
        if expr != old: continue
    #print(expr)
    return int(expr)

print(sum(evaluate2(l) for l in lines))
