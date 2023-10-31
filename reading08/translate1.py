#!/usr/bin/env python3

import re
#from pathlib import Path

regex = re.compile(r'1\d*0:')

counter = 0
for line in open('/etc/passwd'):
	if regex.search(line):
		counter = counter + 1

print(counter)
