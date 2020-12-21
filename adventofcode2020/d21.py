#!/usr/bin/env python3
import sys
from pprint import pprint

lines = sys.stdin.read().splitlines()
allergens={}
all_ingredients=[]
for l in lines:
    recipe = l.split(' (contains ')[0].split()
    a = l.split(' (contains ')[1][:-1].split(', ')
    all_ingredients += recipe
    for a in a:
        if a not in allergens:
            allergens[a] = []
        allergens[a].append(set(recipe))
safe_ingredients = set(all_ingredients)
unsafe={}
for a in allergens:
    recipes = allergens[a]
    safe_ingredients -= set.intersection(*recipes)
    unsafe[a] = set.intersection(*recipes)
print(sum(all_ingredients.count(ingr) for ingr in safe_ingredients))
while True:
    ok=True
    for a in unsafe:
        if len(unsafe[a])>1:
            ok=False
            continue
        for b in unsafe:
            if a!=b:
                unsafe[b] -= unsafe[a]
    if ok:
        break
print(','.join(unsafe[a].pop() for a in sorted(unsafe.keys())))
