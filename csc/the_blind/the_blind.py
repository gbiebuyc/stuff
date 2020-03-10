ct = bytearray(open('ciphertext', 'rb').read())
ct = ct[:len(ct)-44]
ct = ct[5:]
print(ct)
#ct = ct[::-1]
#print(ct)
#for i in ct:
#    print(i)
s = ''
for i in range(1000):
    n = 0;
    j = 0
    while ct[j] != 0x0d:
        n *= 2;
        if ct[j] == 20:
            n += 0
        elif ct[j] == 9:
            n += 1
        j += 1;
    #print(n)
    s += chr(n)
    print(s[::-1])
    ct = ct[j+2:]
