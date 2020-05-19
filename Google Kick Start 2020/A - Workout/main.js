lines = require('fs').readFileSync(0, 'utf8').split('\n')
let numTestCases = parseInt(lines.shift())
for (let i = 0; i < numTestCases; i++) {
    let inputs = lines.shift().split(' ').map(x=>parseInt(x))
    let N = inputs[0]
    let K = inputs[1]
    let sessions = lines.shift().split(' ').map(x=>parseInt(x))

    let maxDiff = 10**9
    let d;
    for (d = 0; d < maxDiff; d++) {
        let additionalSessions = 0
        for (let i = 0; i < N-1; i++) {
            additionalSessions += Math.ceil((sessions[i+1] - sessions[i] - 1) / d)
        }
        if (additionalSessions <= K)
            break
    }
    console.log(`Case #${i+1}: ${d}`)
}
