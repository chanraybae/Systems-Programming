#!/usr/bin/env python3

import sys
import os.path

for arg in sys.argv[1:]:
	if(os.path.exists(arg)):
		print(arg + " exists!")
	else:
		print(arg + " does not exist!")
		sys.exit(1)

