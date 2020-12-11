gridOrig = [list(row.strip()) for row in open('input-11.txt')]
grid = [row.copy() for row in gridOrig]
s=set()
adj=((0,1), (1,1), (1,0), (1,-1), (0,-1), (-1,-1), (-1,0), (-1,1))

def isinside(x, y):
    return x>=0 and y>=0 and x<len(grid[0]) and y<len(grid)

def isoccupied(x, y):
    if isinside(x, y):
        return grid[y][x]=='#'
    return False

while 1:
    newgrid = [row.copy() for row in grid]
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            if grid[y][x]=='L':
                occupied=0
                for dx, dy in adj:
                    if isoccupied(x+dx, y+dy):
                        occupied+=1
                if occupied==0:
                    newgrid[y][x]='#'
            elif grid[y][x]=='#':
                occupied=0
                for dx, dy in adj:
                    if isoccupied(x+dx, y+dy):
                        occupied+=1
                if occupied>=4:
                    newgrid[y][x]='L'
    grid=newgrid
    representation=''.join([item for sublist in grid for item in sublist])
    if representation in s:
        break
    s.add(representation)

representation=''.join([item for sublist in grid for item in sublist])
print(representation.count('#'))



# PART 2

grid = [row.copy() for row in gridOrig]
s=set()

while 1:
    newgrid = [row.copy() for row in grid]
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            if grid[y][x]=='L':
                occupied=0
                for dx, dy in adj:
                    d=1
                    while 1:
                        if not isinside(x+dx*d, y+dy*d):
                            break
                        if grid[y+dy*d][x+dx*d]=='#':
                            occupied+=1
                            break
                        if grid[y+dy*d][x+dx*d]=='L':
                            break
                        d+=1
                if occupied==0:
                    newgrid[y][x]='#'
            elif grid[y][x]=='#':
                occupied=0
                for dx, dy in adj:
                    d=1
                    while 1:
                        if not isinside(x+dx*d, y+dy*d):
                            break
                        if grid[y+dy*d][x+dx*d]=='#':
                            occupied+=1
                            break
                        if grid[y+dy*d][x+dx*d]=='L':
                            break
                        d+=1
                if occupied>=5:
                    newgrid[y][x]='L'
    grid=newgrid
    representation=''.join([item for sublist in grid for item in sublist])
    if representation in s:
        break
    s.add(representation)

representation=''.join([item for sublist in grid for item in sublist])
print(representation.count('#'))
