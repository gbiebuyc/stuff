#!/usr/bin/env python3
import sys
import re

lines = sys.stdin.read().splitlines()
rules={}
messages=[]
for l in lines:
    m = re.match(r'(\d+): (.*)', l)
    if m:
        rules[m.group(1)] = m.group(2)
    elif l!='':
        messages.append(l)

def createRegex(rule_key):
    rule = rules[rule_key]
    if rule[0] == '"':
        return rule[1]
    regex = '('
    for token in rule.split():
        regex += '|' if token=='|' else createRegex(token)
    return regex + ')'

r = createRegex('0')+'$'
print(sum(bool(re.match(r, msg)) for msg in messages))
