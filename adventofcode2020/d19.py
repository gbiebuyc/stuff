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
    regex += ')'
    return regex

regex0 = createRegex('0')+'$'
print(sum(bool(re.match(regex0, msg)) for msg in messages))

regex42 = createRegex('42')
regex31 = createRegex('31')

def part2_match_msg(msg):
    rule42count = 0
    while re.match('^'+regex42, msg):
        msg = re.sub('^'+regex42, '', msg)
        rule42count += 1
    rule31count = 0
    while re.match('^'+regex31, msg):
        msg = re.sub('^'+regex31, '', msg)
        rule31count += 1
    return msg=='' and rule31count>=1 and rule42count>rule31count

print(sum(part2_match_msg(msg) for msg in messages))

