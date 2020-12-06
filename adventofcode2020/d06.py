ans1=0
ans2=0
for group in open('input-06.txt').read().split('\n\n'):
    questions1 = set()
    questions2 = set('abcdefghijklmnopqrstuvwxyz')
    for person in group.split():
        questions1 |= set(person)
        questions2 &= set(person)
    ans1 += len(questions1)
    ans2 += len(questions2)
print(ans1)
print(ans2)
