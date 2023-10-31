#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s PATTERN\n", PROGRAM_NAME);               
    exit(status);
}

bool cat_stream(FILE *stream, char *s) {
    char buffer[BUFSIZ];
    char string[BUFSIZ];
    strcpy(string, s);
	
    bool exit = 1;

    while (fgets(buffer, BUFSIZ, stream)) {
        if(strstr(buffer, s) != NULL){
		fputs(buffer, stdout);   
		exit = 0;      
	}                                     
    }

    return exit;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];                                                          

	if(argc <= 1){
		usage(1);
	}

    while(argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char *arg = argv[argind++];

        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    /* Process each file */
    return cat_stream(stdin, argv[argind]);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
