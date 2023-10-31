#!/usr/bin/env python3

import sys

def evens(stream):
	for x in stream:
		x = x.strip()
		if int(x) % 2 == 0:
			yield x

print(' '.join(evens(sys.stdin)))

