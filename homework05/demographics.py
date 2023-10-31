#!/usr/bin/env python3

import collections
import os
import sys
import csv

import requests

# Constants

URL     = 'https://yld.me/raw/fIRK'
TAB     = ' '*8
GENDERS = ('M', 'F')
ETHNICS = ('B', 'C', 'N', 'O', 'S', 'T', 'U')

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [options] [URL]

    -y  YEARS   Which years to display (default: all)
    -p          Display data as percentages.
    -G          Do not include gender information.
    -E          Do not include ethnic information.
    ''')
    sys.exit(status)

def load_demo_data(url=URL):
    ''' Load demographics from specified URL into dictionary

    >>> load_demo_data('https://yld.me/raw/ilG').keys()
    dict_keys(['2013', '2014', '2015', '2016', '2017', '2018', '2019'])

    >>> load_demo_data('https://yld.me/raw/ilG')['2013'] == \
            {'M': 1, 'B': 2, 'F': 1, 'TOTAL': 2}
    True

    >>> load_demo_data('https://yld.me/raw/ilG')['2019'] == \
            {'M': 1, 'U': 2, 'F': 1, 'TOTAL': 2}
    True
    '''
    # TODO: Request data from url and load it into dictionary organized in the
    # following fashion:
    #
    #   {'year': {'gender': count, 'ethnic': count, 'TOTAL': count}}
    counts = collections.defaultdict(dict)
    response = requests.get(url)
    students = response.text.splitlines()

    for student in csv.DictReader(students):
        year, gender, ethnic = student['Year'], student['Gender'], student['Ethnic']
        counts[year][gender] = counts[year].get(gender, 0) + 1
        counts[year][ethnic] = counts[year].get(ethnic, 0) + 1
        counts[year]['TOTAL'] = counts[year].get('TOTAL', 0) + 1

    return counts

def print_demo_separator(years, char='='):
    ''' Print demographics separator

    Note: The row consists of the 8 chars for each item in years + 1.

    >>> print_demo_separator(['2012', '2013'])
    ========================
    '''
    # TODO: Print row of separator characters
    print(8*char*(len(years)+1))

def print_demo_years(years):
    ''' Print demographics years row

    Note: The row is prefixed by 4 spaces and each year is right aligned to 8
    spaces ({:>8}).

    >>> print_demo_years(['2012', '2013'])
            2012    2013
    '''
    # TODO: Print row of years
    #print(''*3, end = " ")
    
    row = ''
    white = ' '*4
    row += white
    for year in years:
        row += f'{year:>8}'

    print(row)

def print_demo_fields(data, years, fields, percent=False):
    ''' Print demographics information (for particular fields)

    Note: The first column should be a 4-spaced field name ({:>4}), followed by
    8-spaced right aligned data columns ({:>8}).  If `percent` is True, then
    display a percentage ({:>7.1f}%) rather than the raw count.

    >>> data  = load_demo_data('https://yld.me/raw/ilG')
    >>> years = sorted(data.keys())
    >>> print_demo_fields(data, years, GENDERS, False)
       M       1       1       1       1       1       1       1
       F       1       1       1       1       1       1       1
    '''
    # TODO: For each field, print out a row consisting of data from each year.
    row = ''
    for field in fields:
        row += f'{field:>4}'
        for annum in years:
            value = data[annum].get(field, 0)
            if percent:
                value = 100*value/data[annum]['TOTAL']
                row += f'{value:>7.1f}%'
            else:
                row += f'{value:>8}'
        print(row)
        row = ''    


def print_demo_data(data, years=None, percent=False, gender=True, ethnic=True):
    ''' Print demographics data for the specified years and attributes '''
    # TODO: Verify the years parameter (if None then extract from data,
    # otherwise use what is given).  Ensure years is sorted.
    if not years:
        years = data.keys()

    years = sorted(years)

    # TODO: Print years header with separator
    print_demo_years(years)
    print_demo_separator(years)

    # TODO: Print gender and ethic data if enabled
    if gender:
        print_demo_gender(data, years, percent)
    if ethnic:
        print_demo_ethnic(data, years, percent)

def print_demo_gender(data, years, percent=False):
    ''' Print demographics gender information '''
    print_demo_fields(data, years, GENDERS, percent)
    print_demo_separator(years, '-')

def print_demo_ethnic(data, years, percent=False):
    ''' Print demographics ethnic information '''
    print_demo_fields(data, years, ETHNICS, percent)
    print_demo_separator(years, '-')

def main():
    ''' Parse command line arguments, load data from url, and then print
    demographic data. '''
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = URL
    years     = None
    gender    = True
    ethnic    = True
    percent   = False

    while arguments:

        argument = arguments.pop(0)

        if argument.startswith('-'):

            if argument == '-h':
                usage()

            elif argument == '-y':
                years = arguments.pop(0).split(',')

            elif argument == '-p':
                percent = True

            elif argument == '-G':
                gender = False

            elif argument == '-E':
                ethnic = False
            
            else:
                usage(1)

        else:
            url = argument

    # TODO: Load data from url and then print demograpic data with specified
    # arguments
    data = load_demo_data(url)
    print_demo_data(data, years, percent, gender, ethnic)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
