prog = [(l[:3], int(l[4:])) for l in open('input-08.txt')]

def run(i_swap=-1):
    if i_swap>=0 and prog[i_swap][0]=='acc':
        return False, 0
    pc=0
    acc=0
    visited=set()
    while 1:
        if pc == len(prog):
            return True, acc
        if not 0 <= pc < len(prog):
            return False, acc
        if pc in visited:
            return False, acc
        visited.add(pc)
        op, arg = prog[pc]
        if op=='acc':
            acc+=arg
            pc+=1
        elif op=='jmp':
            if pc==i_swap:
                pc+=1
            else:
                pc+=arg
        elif op=='nop':
            if pc==i_swap:
                pc+=arg
            else:
                pc+=1

ret, acc = run()
print(acc)

for i in range(len(prog)):
    ret, acc = run(i)
    if ret:
        print(acc)
        break

