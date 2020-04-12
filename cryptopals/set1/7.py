#!/usr/bin/env python3
import base64
from Crypto.Cipher import AES

ciphertext = base64.b64decode(open('7.txt', 'r').read())
key = b'YELLOW SUBMARINE'
cipher = AES.new(key, AES.MODE_ECB)
plaintext = cipher.decrypt(ciphertext)
print(plaintext.decode())
