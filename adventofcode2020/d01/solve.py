nums = [int(n) for n in open('input')]

def part1():
    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            if nums[i] + nums[j] == 2020:
                return nums[i] * nums[j]

def part2():
    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            for k in range(j+1, len(nums)):
                if nums[i] + nums[j] + nums[k] == 2020:
                    return nums[i] * nums[j] * nums[k]

print('part 1: ', part1())
print('part 2: ', part2())
