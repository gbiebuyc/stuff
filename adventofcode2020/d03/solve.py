lines=open('input').read().splitlines()
def solve(dx, dy):
    x=0
    ans=0
    for l in lines[::dy]:
        ans+=l[x%len(l)]=='#'
        x+=dx
    return ans
print('part 1:', solve(3, 1))
ans=1
for slope in ((1,1), (3,1), (5,1), (7,1), (1,2)):
    ans *= solve(*slope)
print('part 2:', ans)
