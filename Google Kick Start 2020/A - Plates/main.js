
function rec(stackIndex, numTaken) {
    if (stackIndex >= stacks.length)
        return 0
    if (cache[stackIndex][numTaken] != undefined)
        return cache[stackIndex][numTaken]
    let ans = rec(stackIndex+1, numTaken)
    let cur = 0
    for (let i = 0; i < stacks[stackIndex].length && numTaken+i+1 <= numToTake; i++) {
        cur += stacks[stackIndex][i]
        ans = Math.max(ans, cur + rec(stackIndex+1, numTaken+i+1))
    }
    cache[stackIndex][numTaken] = ans
    return ans
}

lines = require('fs').readFileSync(0, 'utf8').split('\n')
numTestCases = parseInt(lines.shift())
for (let i = 0; i < numTestCases; i++) {
    let inputs = lines.shift().split(' ').map(x=>parseInt(x))
    var stacks = Array(inputs[0]).fill().map(() => lines.shift().split(' ').map(x=>parseInt(x)))
    var numToTake = inputs[2]
    var cache = Array(stacks.length).fill().map(() => [])
    let ans = rec(0, 0)
    console.log(`Case #${i+1}: ${ans}`)
}
