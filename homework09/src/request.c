/* request.c: Make HTTP Requests */

#include "request.h"

#include "macros.h"
#include "socket.h"

#include <stdlib.h>
#include <string.h>

/* Constants */

#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'

/* Functions */

/**
 * Construct Request structure by parsing URL string into separate host, port,
 * and path components.
 *
 * @param   url         URL string to parse.
 *
 * @return  Request structure.
 **/
Request *   request_create(const char *url) {
    /* TODO: Copy data to local buffer */
    char *buffer = strdup(url);
    char *loc = buffer;

    /* TODO: Skip scheme to host */
    loc = strstr(buffer, HOST_DELIMITER);
    if(!loc){
        loc = buffer;
    }
    else{
        loc += 3;
    }

    /* TODO: Split host:port from path */
    char *path = strchr(loc, PATH_DELIMITER);
    if(!path){
        path = "";
    }
    else{
        *path = '\0';
        path++;
    }

    /* TODO: Split host and port */
    char *port = strchr(loc, PORT_DELIMITER);
    if(!port){
        port = "80";
    }
    else{
        *port = '\0';
        port++;
    }

    /* TODO: Allocate Request structure */
    Request *request = malloc(sizeof(Request));
    if(request == NULL){
        free(buffer);
        return NULL;
    }

    /* TODO: Copy components to URL structure */
    request->host = strdup(loc);
    request->path = strdup(path);
    request->port = strdup(port);

    free(buffer);

    return request;
}

/**
 * Deallocate Request structure.
 *
 * @param   request     Request structure to deallocate.
 **/
void	    request_delete(Request *request) {
    free(request->host);
    free(request->port);
    free(request->path);
    free(request);
}

/**
 * Make a HTTP request and write the contents of the response to the specified
 * stream.
 *
 * @param   url         Make a HTTP request to this URL.
 * @param   stream      Write the contents of response to this stream.
 *
 * @return  -1 on error, otherwise the number of bytes written.
 **/
ssize_t     request_stream(Request *request, FILE *stream) {
    /* TODO: Connect to remote host and port */
    FILE *client = socket_dial(request->host, request->port);
    if(!client){
        fprintf(stderr, "socket dial not established\n");
        return -1;
    }
    /* TODO: Send request to server */
    fprintf(client, "GET /%s HTTP/1.0\r\n", request->path);
    fprintf(client,"Host: %s\r\n", request->host);
    fprintf(client, "\r\n");
    
    /* TODO: Read response status from server */
    char buffer[BUFSIZ];
    fgets(buffer, BUFSIZ, client);
    if(!strstr(buffer, "200 OK")){
        fprintf(stderr, "unsuccessful request\n");
        return -1;
    }

    /* TODO: Read response headers from server */
    ssize_t content_len = 0;
    while(fgets(buffer, BUFSIZ, client) && strlen(buffer) > 2){
        sscanf(buffer, "Content-length: %lu", &content_len);
    }

    /* TODO: Read response body from server */
    size_t read;
    ssize_t byte_ct = 0;
    while((read = fread(buffer, 1, BUFSIZ, client)) > 0){
        fwrite(buffer, 1, read, stream);
        byte_ct += read;
    }

    /* TODO: Close connection */
    fclose(client);

    /* TODO: Return number of bytes written and check if it matches Content-Length */
    if(content_len == 0 || content_len == byte_ct){
        return byte_ct;
    }

    return -1;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
