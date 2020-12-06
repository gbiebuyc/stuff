ans1=0
ans2=0

def check(i, c, s):
    i = int(i) - 1
    if not 0 <= i < len(s):
        return False
    return s[i] == c

for l in open('input-02.txt'):
    l = l.replace('-', ' ').replace(':', ' ').split()
    if int(l[0]) <= l[3].count(l[2]) <= int(l[1]):
        ans1 += 1
    if check(l[0], l[2], l[3]) ^ check(l[1], l[2], l[3]):
        ans2 += 1
print('part 1: ', ans1)
print('part 2: ', ans2)
