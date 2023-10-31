/* socket.c: TCP Socket Functions */

#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * Create socket connection to specified host and port.
 *
 * @param   host        Host string to connect to.
 * @param   port        Port string to connect to.
 *
 * @return  Socket file stream of connection if successful, otherwise NULL.
 **/
FILE *socket_dial(const char *host, const char *port) {
    /* TODO: Lookup server address information */
    int status;
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
    };
    
    struct addrinfo *servinfo;
    if((status = getaddrinfo(host, port, &hints, &servinfo)) != 0){
        fprintf(stderr, "getaddrinfo failed; %s\n", gai_strerror(status));
        return NULL;
    }

    /* TODO: For each server entry, allocate socket and try to connect */
    int socket_fd = -1;
    for(struct addrinfo *p = servinfo; p != NULL && socket_fd < 0; p = p->ai_next){
        if((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
            fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
            continue;
        } // socket allocation
    
        if(connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0){
            close(socket_fd);
            socket_fd = -1;
            continue;
        } // host connection
    }

    /* TODO: Release allocate address information */
    freeaddrinfo(servinfo);

    /* TODO: Open file stream from socket file descriptor */
    FILE *socket_file = fdopen(socket_fd, "r+");
    if(!socket_file){
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(socket_fd);
        return NULL;
    }
    
    return socket_file;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
