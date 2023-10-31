#!/usr/bin/env python3

import sys

print(' '.join([x for x in [y.strip() for y in sys.stdin] if int(x) % 2 == 0]))
