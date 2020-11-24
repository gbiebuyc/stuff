/**
 * Grab the pellets as fast as you can!
 **/

const {performance} = require('perf_hooks');
const WALL = 1
const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]
var inputs = readline().split(' ');
const width = parseInt(inputs[0]); // size of the grid
const height = parseInt(inputs[1]); // top left corner is (x=0, y=0)
let memory = {
    pellets: Array(height),
}
let map = []
for (let i = 0; i < height; i++) {
    const row = readline(); // one line of the grid: space " " is floor, pound "#" is wall
    map.push(row.split('').map(x => x==' ' ? 0 : 1))
    memory.pellets[i] = map[i].map(cell => cell==WALL ? 0 : 1)
}
function mod(n, m) {
    return ((n % m) + m) % m;
}
function printMap(map) {
    map.forEach((row, i) => {
        console.error(row.map((e, j) => {
            if (memory.pellets[i][j] == 10) return 'S'
            if (memory.pellets[i][j]) return '*'
            if (e == WALL) return '#'
            return ' '
        }).join(''))
    })
}
function getNeighbors(map, p) {
    return directions.map(dir => (
        {x: mod(p.x+dir[0], width), y: p.y+dir[1]}
        )).filter(p => map[p.y][p.x] != WALL)
}
let paths = Array(height).fill().map(() => [])
for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
        if (map[y][x] == WALL)
            continue
        let result = []
        let queue = [{x, y, path: []}]
        let discovered = Array(height).fill().map(() => [])
        discovered[y][x] = true
        while (queue.length) {
            let current = queue.shift()
            getNeighbors(map, current).forEach(neighbor => {
                if (!discovered[neighbor.y][neighbor.x]) {
                    discovered[neighbor.y][neighbor.x] = true
                    neighbor.path = current.path.concat({x: neighbor.x, y: neighbor.y})
                    queue.push(neighbor)
                    result.push(neighbor.path)
                }
            })
        }
        paths[y][x] = result
    }
}
function isSuperPellet(pellet) {
    return pellet > 5
}

// game loop
while (true) {
    var inputs = readline().split(' ');
    const myScore = parseInt(inputs[0]);
    const opponentScore = parseInt(inputs[1]);
    const visiblePacCount = parseInt(readline()); // all your pacs and enemy pacs in sight
    let pacs = Array(height).fill().map(() => [])
    for (let i = 0; i < visiblePacCount; i++) {
        var inputs = readline().split(' ');
        const pacId = parseInt(inputs[0]); // pac number (unique within a team)
        const mine = inputs[1] !== '0'; // true if this pac is yours
        const x = parseInt(inputs[2]); // position in the grid
        const y = parseInt(inputs[3]); // position in the grid
        const typeId = inputs[4]; // unused in wood leagues
        const speedTurnsLeft = parseInt(inputs[5]); // unused in wood leagues
        const abilityCooldown = parseInt(inputs[6]); // unused in wood leagues
        if (typeId == 'DEAD')
            continue
        pacs[y][x] = {x, y, mine, pacId, abilityCooldown}
    }
    const visiblePelletCount = parseInt(readline()); // all pellets in sight
    let pellets = Array(height).fill().map(() => Array(width).fill(0))
    for (let i = 0; i < visiblePelletCount; i++) {
        var inputs = readline().split(' ');
        const x = parseInt(inputs[0]);
        const y = parseInt(inputs[1]);
        const value = parseInt(inputs[2]); // amount of points this pellet is worth
        if (isSuperPellet(value))
            memory.pellets[y][x] = value
        pellets[y][x] = value
    }
    // let start = performance.now()

    // Update memory
    let myPacs = pacs.flat().filter(pac => pac.mine)
    myPacs.forEach(pac => {
        directions.forEach(dir => {
            let cell = {...pac}
            let count = 0
            while (map[cell.y][cell.x] != WALL && count++ < width) {
                memory.pellets[cell.y][cell.x] = pellets[cell.y][cell.x]
                cell.x = mod(cell.x+dir[0] , width)
                cell.y += dir[1]
            }
        })
    })
    // Remove eaten SuperPellets from memory
    for (let i = 0; i < height; i++) {
        for (let j = 0; j < width; j++) {
            if (isSuperPellet(memory.pellets[i][j])) {
                memory.pellets[i][j] = pellets[i][j]
            }
        }
    }

    let outputCommands = []
    let visited = Array(height).fill().map(() => Array(width).fill(0))
    for (let pac of myPacs) {
        if (pac.abilityCooldown == 0) {
            outputCommands.push(`SPEED ${pac.pacId}`)
            continue
        }
        let possiblePaths = paths[pac.y][pac.x]
            // .filter(path => path.length <= 15 && path.length)
            .map(path => {
                let score = 0;
                path.forEach((cell, i) => {
                    let cellScore = memory.pellets[cell.y][cell.x]*2
                    if (pacs[cell.y][cell.x])
                        cellScore -= 10
                    cellScore -= visited[cell.y][cell.x]
                    cellScore /= (i + 1)
                    score += cellScore
                })
                return {path, score}
            })
            .sort((a, b) => {
                return b.score - a.score
            })
        let bestPath = possiblePaths.length ? possiblePaths[0].path : [pac]
        console.error(`pac${pac.pacId} path:`, bestPath)
        bestPath.forEach((cell, i) => visited[cell.y][cell.x] += 10 / (i+1))
        let nextMove = bestPath[bestPath.length > 1 ? 1 : 0]
        outputCommands.push(`MOVE ${pac.pacId} ${nextMove.x} ${nextMove.y} me`)
    }

    printMap(map)
    // console.error(performance.now() - start)
    console.log(outputCommands.join(' | '))
}

