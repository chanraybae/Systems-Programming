#!/usr/bin/env python3

import os
import re
import csv

stringz = []
for line in os.popen('/bin/ls -l /etc'):	
	line = line.split()
	if len(line) < 3:
		continue
	string = line[3]
	
	if string not in stringz:
		stringz.append(string)

stringz.sort()

for string in stringz:
	print(string)
