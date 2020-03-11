#!/usr/bin/env python3

buf = open('csc-keylogger.exe_200212_200703.dmp', 'rb').read()[0x81f47:]
print('szMarker: ', buf[:32])
count = int.from_bytes(buf[36:40], 'little')
print('iCounter: ', count)
buf = buf[40:]
s = ''
for i in range(count):
	s += chr(int.from_bytes(buf[i*20:i*20+4], 'little'))
	print(s)
# CSC{AZERTYCFOTER123OPC}