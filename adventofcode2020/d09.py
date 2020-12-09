numbers = [int(l) for l in open('input-09.txt')]

preamble_len = 25

ans=0
for i in range(preamble_len, len(numbers)):
    valid=0
    for j in range(i-preamble_len, i):
        if valid:
            break
        for k in range(j+1, i):
            if numbers[j]+numbers[k]==numbers[i]:
                valid=1
                break
    if not valid:
        ans=numbers[i]
        break

print(ans)

for i in range(len(numbers)):
    sum=0
    smallest=numbers[i]
    largest=numbers[i]
    for j in range(i, len(numbers)):
        smallest=min(smallest, numbers[j])
        largest=max(largest, numbers[j])
        sum+=numbers[j]
        if sum==ans:
            print(smallest+largest)
            exit(0)
