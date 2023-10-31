#!/usr/bin/env python3

import re
import os

counter = {}

for string in open('/etc/passwd'):
	string = string.split(':')
	string = string[6]
	string = string.strip()

	if string not in counter:
		counter[string] = 1
	else:
		counter[string] = counter[string] + 1

counter1 = {}
for keys,values in sorted(counter.items()):
	counter1[keys] = values

counter_list = sorted(counter1.items(), key = lambda x: x[1], reverse = True)

for line in counter_list:
	key = line[0]
	value = line[1]
	print(f'{value:>7} {key}')
