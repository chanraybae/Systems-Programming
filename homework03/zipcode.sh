#!/bin/sh

# Globals

URL=https://www.zipcodestogo.com/
STATE=Indiana/
CITY=

# Functions

usage() {
	cat 1>&2 <<EOF
Usage: $(basename $0)
 
-c      CITY    Which city to search
-s      STATE   Which state to search (Indiana)
 
If no CITY is specified, then all the zip codes for the STATE are displayed.
EOF
	exit $1	
}

website_zips() {
	# used to remove the spaces between state names if applicable
	curl -sL "$URL$(echo -n $STATE | sed "s/ /%20/g")/"
}


get_zips() {
	# retrieving the values from the server
	sed -nE "s/^.*<a href=\"\/\/www.zipcodestogo.com\/([^\/]*)\/[^\/]*\/([^\/]*)\/\">.+$/\1:\2/p"
}

city_filter_state() {
	# filtering by city if applicable but defaults to printing every zipcode in state
	if [ ! -z "$CITY" ]; then
		grep "$CITY:" | sed 's/[^0-9]*//g'
	else
		cat | sed 's/[^0-9]*//g' # only showing zipcode
	fi
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
    -h) usage 0;;
	-c) CITY=$2; shift;;
	-s) STATE=$2; shift;;
     *) usage 1;;
    esac
    shift
done

# Filter Pipeline(s)
#curl -s $URL
website_zips | get_zips | city_filter_state
