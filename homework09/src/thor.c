/* thor.c */

#include "hammer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] URL\n", progname);
    fprintf(stderr, "    -n HAMMERS How many times to hammer the URL\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    size_t req = 1;
    int arg = 1; //iterator for the command line
    char *link = "";

    while(arg < argc && argv[arg][0] == '-'){
        if(argv[arg][1] == 'h'){
            usage(argv[0], 0);
        }
        else if(argv[arg][1] == 'n'){
            req = atoi(argv[++arg]);
        }
        else{
            usage(argv[0], 1);    
        }
        ++arg;
    }

    if(arg < argc){
        link = argv[arg];
    }
    else{
        usage(argv[0], 1);
    }
    /* TODO: Throw Hammers */
    bool theHammers = throw(link, req, stdout);
    if(theHammers){
        return EXIT_SUCCESS;
    }
    // defaulting
    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
