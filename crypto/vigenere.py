import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-d', '--decrypt', action='store_true')
parser.add_argument('text')
parser.add_argument('key')
args = parser.parse_args()
#args = parser.parse_args(['-d', 'GCYCZFMLYLEIM', 'AYUSH'])
result = ''
for i in range(len(args.text)):
    c = args.text[i].upper()
    c2 = args.key[i % len(args.key)].upper()
    i1 = ord(c)-65
    i2 = ord(c2)-65
    i3 = (i1 - i2) if args.decrypt else (i1 + i2)
    i3 %= 26
    result += chr(i3+65)
print('input: ', args.text)
print('key:   ', args.key)
print('result:', result)
