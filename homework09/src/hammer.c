/* hammer.c: Make HTTP request and measure bandwidth */

#include "hammer.h"
#include "macros.h"
#include "request.h"
#include "timestamp.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Constants */

#define MEGABYTE    (double)(1<<20)

/* Functions */

/**
 * Perform a hammer through by making a HTTP request to the specified URL and
 * printing the contents of the response to the given stream.
 * Function prints the bandwidth of the HTTP transaction if it is successful to
 * stderr.
 *
 * @param   url         Make HTTP request to this URL.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not the HTTP request was successful.
 **/
bool	hammer(const char *url, FILE *stream) {
    Request* rq = request_create(url);

    if(!rq)
        return NULL;

    double start_time = timestamp();
    ssize_t bytes_written = request_stream(rq, stream);
    double end_time = timestamp();
    double bandwidth = bytes_written / 1048576.0 / (end_time - start_time);

    if(bytes_written >= 0){
        fprintf(stderr, "Bandwidth: %0.2lf MB/s\n", bandwidth);
        request_delete(rq);
        return true;
    }
    else{
        request_delete(rq);
        return false;
    }
    // default statement
    return false;
}

/**
 * Make hammers HTTP requests to the specified url, while writing the contents
 * of the request to the specified stream.
 *
 * Each HTTP request must be performed by a separate child process.
 *
 * Function prints the total elapsed time for all throws to stderr at the end.
 *
 * @param   url         Make HTTP requests to this URL.
 * @param   hammers     The number of HTTP requests to make.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not all hammer throws were successful.
 **/
bool	throw(const char *url, size_t hammers, FILE *stream) {
    /* TODO: Throw all hammers by spawning child processes that call hammer and
     * exit success if the hammer throw was successful. */
    double start_time = timestamp();
    for(int i = 0; i < hammers; i++){
        pid_t pid = fork();

        if(pid < 0){
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            if(!hammer(url, stream)){
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }

    /* TODO: Collect results of throws by waiting for all children */
    int all_status = 0;
    for(int i = 0; i < hammers; i++){
        int child_status;
        while(wait(&child_status) < 0){}
        all_status += child_status;
    }

    /* TODO: Print elapsed time to stderr */
    double elapsed_time = timestamp() - start_time;
    fprintf(stderr, "Elapsed Time: %0.2lf seconds\n", elapsed_time);
    
    // whether hammer throws successful
    return all_status == 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
