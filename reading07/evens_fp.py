#!/usr/bin/env python3

import sys

print(' '.join(filter(lambda x: int(x) % 2 == 0, map(lambda y: y.strip(), sys.stdin))))
