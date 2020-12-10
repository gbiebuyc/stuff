nums = [0] + [int(l) for l in open('input-10.txt')]
nums.sort()
diff1=0
diff3=1
for i in range(1, len(nums)):
    if nums[i]-nums[i-1] == 1:
        diff1+=1
    if nums[i]-nums[i-1] == 3:
        diff3+=1
#print(diff1)
#print(diff3)
print(diff1*diff3)

dp = [None]*len(nums)

def solve(i):
    if dp[i] is not None:
        return dp[i]
    if i==len(nums)-1:
        return 1
    ret=0
    for j in range(i+1, min(len(nums), i+4)):
        if nums[j]-nums[i]<=3:
            ret += solve(j)
    dp[i] = ret
    return ret

print(solve(0))
