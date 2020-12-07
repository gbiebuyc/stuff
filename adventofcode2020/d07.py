rules = {}
for rule in open('input-07.txt'):
    k, v = rule.split(' bags contain ')
    v = [] if 'no other' in v else v.split(', ')
    v = [(v.split(' bag')[0][2:], int(v[0])) for v in v]
    rules[k] = v

def part1(bag):
    return any(bag=='shiny gold' or part1(bag) for bag, _ in rules[bag])

def part2(bag):
    return 1 + sum([count*part2(bag) for bag, count in rules[bag]])

print(sum(map(part1, rules)))
print(part2('shiny gold')-1)
