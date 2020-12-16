#!/usr/bin/env python3
import sys

lines = sys.stdin.read().splitlines()
ranges=[]
for l in lines[:20]:
	mn, mx = l.split()[-3].split('-')
	ranges.append((int(mn), int(mx)))
	mn, mx = l.split()[-1].split('-')
	ranges.append((int(mn), int(mx)))

ticket_scanning_error_rate=0
valid_tickets=[]
for l in lines[25:]:
	all_valid=1
	for val in l.split(','):
		val=int(val)
		valid=0
		for r in ranges:
			if r[0] <= val <= r[1]:
				valid=1
				break
		if not valid:
			all_valid=0
			ticket_scanning_error_rate += val
	if all_valid:
		valid_tickets.append(l)
print(ticket_scanning_error_rate)

possible=[set(range(20)) for _ in range(20)]
for i in range(20):
	for l in valid_tickets:
		val=int(l.split(',')[i])
		x = []
		for i_range, r in enumerate(ranges):
			if r[0] <= val <= r[1]:
				x.append(i_range//2)
		possible[i] &= set(x)
for _ in range(1000):
	for p in possible:
		if len(p) == 1:
			for pp in possible:
				if len(pp) != 1:
					pp -= p
ans=1
for i in range(20):
	if list(possible[i])[0] < 6:
		ans *= int(lines[22].split(',')[i])
print(ans)
