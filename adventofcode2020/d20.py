#!/usr/bin/env python3
from sys import stdin

tiles={}
for tile in stdin.read().strip().split('\n\n'):
    tiles[int(tile[5:9])] = [list(row) for row in tile.splitlines()[1:]]
firstTileNo, firstTile = list(tiles.items())[0]
TILE_SZ = len(firstTile)-2
SIDE_TILES = int(len(tiles)**.5)
IMAGE_SZ = TILE_SZ * SIDE_TILES

def get_border(tileNo, border):
    tile = tiles[tileNo]
    if border==0:
        return tile[0]
    if border==1:
        return [row[-1] for row in tile]
    if border==2:
        return tile[-1][::-1]
    if border==3:
        return [row[0] for row in tile][::-1]

def rotate(tile, n):
    for _ in range(n%4):
        tile = [list(row) for row in zip(*tile[::-1])]
    return tile

def flip_vertical(tile): return tile[::-1]
def flip_horizontal(tile): return [row[::-1] for row in tile]

def check(cur, borderNo, other):
    border = get_border(cur, borderNo)
    for otherBorderNo in range(4):
        otherBorder = get_border(other, otherBorderNo)
        if border == otherBorder:
            tiles[other] = rotate(tiles[other], borderNo - otherBorderNo + 2)
            tiles[other] = flip_vertical(tiles[other]) if borderNo%2 else flip_horizontal(tiles[other])
            return True
        if border == otherBorder[::-1]:
            tiles[other] = rotate(tiles[other], borderNo - otherBorderNo + 2)
            return True
    return False

corners=[]
borders={}
topleft=None

def find_borders(cur):
    global topleft
    if cur in borders:
        return
    borders[cur] = [0,0,0,0]
    for other in tiles:
        if cur == other:
            continue
        for border in range(4):
            if check(cur, border, other):
                borders[cur][border] = other
    if borders[cur].count(0) == 2:
        corners.append(cur)
        if borders[cur][1] and borders[cur][2]:
            topleft=cur
    for b in borders[cur]:
        if b:
            find_borders(b)

find_borders(firstTileNo)
print(f'corners: {corners}')
print(corners[0] * corners[1] * corners[2] * corners[3])

image = [[None]*IMAGE_SZ for _ in range(IMAGE_SZ)]
tileY = topleft
for y in range(0, IMAGE_SZ, TILE_SZ):
    tileX = tileY
    for x in range(0, IMAGE_SZ, TILE_SZ):
        for yy, row in enumerate(tiles[tileX][1:-1]):
            for xx, cell in enumerate(row[1:-1]):
                image[y+yy][x+xx] = cell
        tileX = borders[tileX][1]
    tileY = borders[tileY][2]
image = rotate(image, 1)
monster = ['                  # ',
           '#    ##    ##    ###',
           ' #  #  #  #  #  #   ']
MONSTER_NUM_CHARS = sum(row.count('#') for row in monster)

num_monsters=0
for image in (rotate(image, n) for n in range(4)):
    for image in (image, flip_vertical(image), flip_horizontal(image)):
        for y in range(IMAGE_SZ - len(monster)):
            for x in range(IMAGE_SZ - len(monster[0])):
                valid = 1
                for yy in range(len(monster)):
                    for xx in range(len(monster[0])):
                        if monster[yy][xx]=='#' and image[y+yy][x+xx]!='#':
                            valid=0
                            break
                    if not valid:
                        break
                if valid:
                    num_monsters += 1
        if num_monsters:
            break
    if num_monsters:
        break
IMAGE_NUM_CHARS = sum(row.count('#') for row in image)
ans = IMAGE_NUM_CHARS - num_monsters * MONSTER_NUM_CHARS
print(ans)
