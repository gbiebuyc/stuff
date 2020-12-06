def decode(code):
    F=0
    B=127
    L=0
    R=7
    for c in code[:7]:
        mid = F+(B-F)//2
        if c=='F':
            B=mid
        elif c=='B':
            F=mid+1

    for c in code[7:10]:
        mid = L+(R-L)//2
        if c=='L':
            R=mid
        elif c=='R':
            L=mid+1
    return F*8+L

ans=0
seats=[0]*128*8
for code in open('input-05.txt'):
    seatID = decode(code)
    ans = max(ans, seatID)
    seats[seatID] = 1
print('part 1:', ans)
for i in range(1, len(seats)-1):
    if seats[i]==0 and seats[i-1] and seats[i+1]:
        print('part 2:', i)
        break
