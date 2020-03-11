#!/usr/bin/env python3

buf = open('csc-keylogger.exe_200212_200703.dmp', 'rb').read()[0x81f47:]
print('szMarker: ', buf[:32])
print(int.from_bytes(buf[32:40], 'little'))
print(int.from_bytes(buf[40:48], 'little'))
