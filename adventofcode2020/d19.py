#!/usr/bin/env python3
import sys
import re

lines = sys.stdin.read().splitlines()
rules={}
messages=[]
for l in lines:
    m = re.match(r'(\d+): (.*)', l)
    if m:
        rules[int(m.group(1))] = m.group(2)
    elif l!='':
        messages.append(l)
#print(rules)
#print(messages)

def get_possibilities(rule):
    rule = rules[rule]
    if rule[0] == '"':
        return [rule[1]]
    possibilities=[]
    for p in rule.split('|'):
        x=['']
        for r in p.split():
            x = [a + b for a in x for b in get_possibilities(int(r))]
        possibilities += x
    return possibilities

#print(get_possibilities(0))
p = get_possibilities(0)
print(sum(msg in p for msg in messages))
