/* duplicates.c */

#include "hash.h"
#include "macros.h"
#include "table.h"

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Structures */

typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "    -c     Only display total number of duplicates\n");
    fprintf(stderr, "    -q     Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

/**
 * Check if path is a directory.
 * @param       path        Path to check.
 * @return      true if Path is a directory, otherwise false.
 */
bool is_directory(const char *path) {
    struct stat s;

    if(stat(path, &s) == 0 && S_ISDIR(s.st_mode)){
        return true;
    }

    return false;
}

/**
 * Check if file is in table of checksums.
 *
 *  If quiet is true, then exit if file is in checksums table.
 *
 *  If count is false, then print duplicate association if file is in
 *  checksums table.
 *
 * @param       path        Path to file to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      0 if Path is not in checksums, otherwise 1.
 */
size_t check_file(const char *path, Table *checksums, Options *options) {
    char hexdigest[HEX_DIGEST_LENGTH];
    if(!hash_from_file(path, hexdigest)){
        return -1;
    }
    Value *val = table_search(checksums, hexdigest);

    if(!val){
        table_insert(checksums, hexdigest, (Value)(char *)path, STRING);
    }
    else{
        if(!options->count){
            printf("%s is a duplicate of %s\n", path, val->string);
        }
        if(options->quiet){
            exit(EXIT_SUCCESS);
        }
        return 1;
    }

    return 0;
}

/**
 * Check all entries in directory (recursively).
 * @param       root        Path to directory to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      Number of duplicate entries in directory.
 */
size_t check_directory(const char *root, Table *checksums, Options *options) {
    int counter = 0;
    DIR *direc = opendir(root);

    for (struct dirent *e = readdir(direc); e; e = readdir(direc)){
        if (streq(e->d_name, ".") || streq(e->d_name, "..")){
            continue;
        }

        char path[BUFSIZ];
        sprintf(path, "%s/%s", root, e->d_name);

        if(is_directory(path)){
            counter = counter + check_directory(path, checksums, options);
        }
        else{
            counter = counter + check_file(path, checksums, options);
            if(options->quiet && counter == 1){
                closedir(direc);
                return counter;
            }
        }
    }
    
    closedir(direc);
    return counter;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    Table *t = table_create(0); 
    Options op = {false, false};
    int argind = 1;
    char array_dir[argc-1][BUFSIZ];
    int index_dir = 0;
    int counter = 0;

    while(argind < argc){
        char *arg = argv[argind++];

        if(arg[0] == '-'){
            if(arg[1] == 'c')
                op.count = true;
            else if (arg[1] == 'q')
                op.quiet = true;
            else if (arg[1] == 'h')
                usage(0);
        }

        else{
            strcpy(array_dir[index_dir], arg);
            index_dir++;
        }
    }

    /* Check each argument */
    for(int i = 0; i < index_dir; i++){
        if(is_directory(array_dir[i])){
            counter = counter + check_directory(array_dir[i], t, &op);
        }
        else{
            counter = counter + check_file(array_dir[i], t, &op);
        }
    }

    /* Display count if necessary */
    table_delete(t);
    if(op.count){
        printf("%d\n", counter);   
    }

    if (op.quiet){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
