#!/usr/bin/env python3
from sys import stdin

data = stdin.read()
player1, player2 = [[int(x) for x in x.splitlines()[1:]] for x in data.split('\n\n')]

def part1(player1, player2):
    while len(player1) and len(player2):
        draw1 = player1.pop(0)
        draw2 = player2.pop(0)
        if draw1 > draw2:
            player1 += [draw1, draw2]
        elif draw2 > draw1:
            player2 += [draw2, draw1]
    return player1, player2

def calc_score(deck):
    return sum((i+1)*score for i, score in enumerate(deck[::-1]))

#game=0
def part2(player1, player2):
    #global game
    #game+=1
    #thisgame=game
    #print()
    #print(f'=== Game {thisgame} ===')
    #round=0
    rounds=[]
    while len(player1) and len(player2):
        #round+=1
        #print(f'-- Round {round} (Game {thisgame}) --')
        #print(player1)
        #print(player2)
        cur_round = str([player1, player2])
        if cur_round in rounds:
            return 1, player1, player2
        rounds.append(cur_round)
        draw1 = player1.pop(0)
        draw2 = player2.pop(0)
        winner = 1 if draw1>draw2 else 2
        if len(player1) >= draw1 and len(player2) >= draw2:
            winner, _, _ = part2(player1[:draw1], player2[:draw2])
        if winner == 1:
            player1 += [draw1, draw2]
        else:
            player2 += [draw2, draw1]
    return 1 if len(player1) else 2, player1, player2

result1, result2 = part1(player1[:], player2[:])
print(calc_score(result1+result2))
_, result1, result2 = part2(player1[:], player2[:])
print(calc_score(result1+result2))

