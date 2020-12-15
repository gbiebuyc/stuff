#!/usr/bin/env python3

inp='402328-864247'
mn = int(inp.split('-')[0])
mx = int(inp.split('-')[1])

def solve(is_part2):
    ans=0
    for i in range(mn, mx+1):
        s=str(i)
        valid=0
        for j in range(10):
            if is_part2 and str(j)*3 in str(i):
                continue
            if str(j)*2 in str(i):
                valid=1
        if not valid: continue
        valid=1
        for j in range(1, 6):
            if not int(str(i)[j-1])<=int(str(i)[j]):
                valid=0
        if not valid: continue
        ans+=1
    return ans

print(solve(False))
print(solve(True))
