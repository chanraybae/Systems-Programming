/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Flags */

enum {
    /* TODO*: Enumerate Flags */
    STRIP = 1 << 0,
    REVERSE = 1 << 1,
    LOWER = 1 << 2,
    UPPER = 1 << 3,
    TITLE = 1 << 4
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    fprintf(stderr, "   -t      Convert to titlecase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int flag) {
    /* TODO: Process each line in stream by performing transformations */
    int f = flag;
    char buffer[BUFSIZ];
    while( fgets(buffer, BUFSIZ, stream) ){
        str_chomp(buffer);
        str_translate(buffer, source, target);
        if (f & STRIP)
            str_strip(buffer);
        if (f & REVERSE)
            str_reverse(buffer);
        if (f & LOWER)
            str_lower(buffer);
        if (f & UPPER)
            str_upper(buffer);
        if(f & TITLE)
            str_title(buffer);

        printf("%s\n", buffer);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    int argind = 1;
    int flag = 0;
    PROGRAM_NAME = argv[0];
    while(argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char *arg = argv[argind++];
        switch (arg[1]){
            case 'h':
                usage(0);
                break;
            case 's':
                flag |= STRIP;
                break;
            case 'r':
                flag |= REVERSE;
                break;
            case 'l':
                flag |= LOWER;
                break;
            case 'u':
                flag |= UPPER;
                break;
            case 't':
                flag |= TITLE;
                break;
            default:
                usage(1);
                break;
        }
    }

    // translate stream
    if (argc > 2)
        translate_stream(stdin, argv[argc-2], argv[argc-1], flag);
    else
        translate_stream(stdin, "", "", flag);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
