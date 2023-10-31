#!/usr/bin/env python3

import collections
import re
import requests

# Globals

URL = 'https://cse.nd.edu/undergraduate/computer-science-curriculum/'

# Initialize a default dictionary with integer values
counts = collections.defaultdict(int)

# TODO: Make a HTTP request to URL
response = requests.get(URL)

# TODO: Access text from response object
data = response.text

# TODO: Compile regular expression to match CSE courses (ie. CSE XXXXX)
regex = re.compile(r'CSE (\d)\d\d\d\d')

# TODO: Search through data using compiled regular expression and count up all
# the courses per class year
for course in re.findall(regex, data):
	counts[course] = counts.get(course,0) + 1

# TODO: Sort items in counts dictionary by value in reverse order and
# display counts and class year
for year, count in sorted(counts.items(), key=lambda p: p[1], reverse = 1):
	if year == '4':
		year = 'Senior'	
	elif year == '3':
		year = 'Junior'
	elif year == '2':
		year = 'Sophomore'

	print(f'{count:>7} {year}')
