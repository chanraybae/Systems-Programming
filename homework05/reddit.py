#!/usr/bin/env python3

import os
import sys

import requests

# Constants

ISGD_URL = 'http://is.gd/create.php'

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL_OR_SUBREDDIT

    -s          Shorten URLs using (default: False)
    -n LIMIT    Number of articles to display (default: 10)
    -o ORDERBY  Field to sort articles by (default: score)
    -t TITLELEN Truncate title to specified length (default: 60)
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_reddit_data(url):
    ''' Load reddit data from specified URL into dictionary

    >>> len(load_reddit_data('https://reddit.com/r/nba/.json')) >= 25
    True

    >>> load_reddit_data('linux')[0]['data']['subreddit']
    'linux'
    '''
    # TODO: Verify url parameter (if it starts with http, then use it,
    # otherwise assume it is just a subreddit).
    if url.startswith('http') == False:
        redditURL = 'https://www.reddit.com/r/'
        url = redditURL + url
        jsonString = '/.json'
        url = url + jsonString
    
    headers  = {'user-agent': 'reddit-{}'.format(os.environ.get('USER', 'cse-20289-sp22'))}
    response = requests.get(url, headers=headers)
    redditData = response.json()
    
    childrenData = redditData['data']['children']
    
    return childrenData
                

def shorten_url(url):
    ''' Shorten URL using is.gd service

    >>> shorten_url('https://reddit.com/r/aoe2')
    'https://is.gd/dL5bBZ'

    >>> shorten_url('https://cse.nd.edu')
    'https://is.gd/3gwUc8'
    '''
    # TODO: Make request to is.gd service to generate shortened url.
    response = requests.get(ISGD_URL, params={'format': 'json', 'url': url})

    return response.json()['shorturl']

def print_reddit_data(data, limit=10, orderby='score', titlelen=60, shorten=False):
    ''' Dump reddit data based on specified attributes '''
    # TODO: Sort articles stored in data list by the orderby key, and then
    # print out each article's index, title, score, and url using the following
    # format:
    #
    #   print(f'{index:4}.\t{title} (Score: {score})\n\t{url}')
    #
    # Note: Trim or modify the output based on the keyword arguments to the function.
    if orderby == 'score':
        articles = sorted(data, key=lambda i: i['data'][orderby], reverse = True)

    else: 
        articles = sorted(data, key=lambda i: i['data'][orderby])

    for counter, article in enumerate(articles[0:limit]):

        if titlelen < len(article['data']['title']):
            article['data']['title'] = article['data']['title'][0:titlelen]

        if shorten:
            article['data']['url'] = shorten_url(article['data']['url'])

        index = counter + 1

        title = article['data']['title']
        score = article['data']['score']
        url = article['data']['url']

        if index > 1:
            print()

        print(f'{index:4}.\t{title} (Score: {score})\n\t{url}')

def main():
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = None
    limit     = 10
    orderby   = 'score'
    titlelen  = 60
    shorten   = False

    if len(sys.argv) == 1:
        usage(1)

    while arguments:

        argument = arguments.pop(0)

        if argument == '-h':
            usage()

        elif argument == '-s':
            shorten = True

        elif argument == '-n':
            limit = int(arguments.pop(0))
            
        elif argument == '-o':
            orderby = arguments.pop(0)

        elif argument == '-t':
            titlelen = int(arguments.pop(0))

        else:
            url = argument
    
    # TODO: Load data from url and then print the data
    data = load_reddit_data(url)
    print_reddit_data(data, limit, orderby, titlelen, shorten)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
