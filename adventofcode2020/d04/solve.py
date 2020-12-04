import re

passports = open('input').read().split('\n\n')
ans=0
for p in passports:
    byr=0
    iyr=0
    eyr=0
    hgt=0
    hcl=0
    ecl=0
    pid=0
    valid=1
    for field in p.split():
        if re.match(r'byr:(19[2-9]\d|200[0-2])$', field): byr=1
        elif re.match(r'iyr:(201\d|2020)$', field): iyr=1
        elif re.match(r'eyr:(202\d|2030)$', field): eyr=1
        elif re.match(r'hgt:(1[5-8]\d|19[0-3])cm$', field): hgt=1
        elif re.match(r'hgt:(59|6\d|7[0-6])in$', field): hgt=1
        elif re.match(r'hcl:#[0-9a-f]{6}$', field): hcl=1
        elif re.match(r'ecl:(amb|blu|brn|gry|grn|hzl|oth)$',
                field): ecl=1
        elif re.match(r'pid:\d{9}$', field): pid=1
        elif re.match(r'cid:.*', field): pass
        else: valid=0
    if byr and iyr and eyr and hgt and hcl and ecl and pid and valid:
        ans += 1

print(ans)
