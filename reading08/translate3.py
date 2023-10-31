#!/usr/bin/env python3

import re
import requests

strings = requests.get('http://yld.me/raw/fDIO').text
regex1 = re.compile(r'M.*')

names = []
for string in re.findall(regex1,strings):
	#extCheck = ','.find(string)
	if string.startswith('M'): # if statement is for the modification in the regex
		string = string.split(',')
		#print(string)
		if len(string) > 1:
			string = string[1::]
		names.append(string[0])

names.sort()

for name in names:
	if name.startswith('M'):
		print(name)
