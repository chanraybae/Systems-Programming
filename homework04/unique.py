#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]

    -c      Prefix lines by the number of occurences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines

By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    frequencies = {}

    for line in stream:
        line = line.strip()

        if ignore_case:
            line = line.lower()

        frequencies[line] = frequencies.get(line, 0) + 1

    return frequencies

def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:

    - occurrences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    for string in frequencies.keys():
        # does not print if conditions not met
        if(duplicates and frequencies[string] == 1) or (unique_only and frequencies[string] > 1):
            continue

        if occurrences:
            print(f'{frequencies[string]:>7} {string}')
        else:
            print(string)

def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''
    #if len(sys.argv) == 2:
     #   if (sys.argv[1] == '-h'):
      #      usage()
       # else:
        #    usage(1)

    #boolean variables for function input
    occurrences = False
    duplicates = False
    ignore_case = False
    unique_only = False

    # args
    arguments = sys.argv[1:]

    while arguments and arguments[0].startswith('-'):
        argument = arguments.pop(0)

        if argument == '-h':
            usage()
        elif argument == '-c':
            occurrences = True
        elif argument == '-d':
            duplicates = True
        elif argument == '-i':
            ignore_case = True
        elif argument == '-u':
            unique_only = True
        else:
            usage(1)

    frequencies = count_frequencies(sys.stdin, ignore_case)
    print_lines(frequencies, occurrences, duplicates, unique_only)


# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
