/* timestamp.c: Timestamp Functions */

#include "timestamp.h"

#include <time.h>
#include <sys/time.h>

/**
 * Return current timestamp as a double.
 *
 * Utilizes gettimeofday for precision (accounting for seconds and
 * microseconds) and falls back to time (only account for seconds) if that
 * fails.
 *
 * @return  Current time as a double.
 **/
double timestamp() {
    struct timeval getTime;
    if(gettimeofday(&getTime, NULL) == -1 ){
        return time(NULL);
    }
    
    return ((double)getTime.tv_sec + ((double)getTime.tv_usec / 1000000.0));
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
