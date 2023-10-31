/* pair.c: Key/Value Pair */

#include "pair.h"

#include <stdlib.h>
#include <string.h>

/**
 * Create Pair structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   next            Reference to next pair.
 * @param   type            Pair's value's type.
 * @return  Allocated Pair structure.
 */
Pair *	    pair_create(const char *key, const Value value, Pair *next, Type type) {
    Pair *p = malloc(sizeof(Pair));

    if (p == NULL)
        return NULL;

    p->key = strdup(key);
    if(type == STRING){
        p->value.string = strdup(value.string);
        p->type = STRING;
    }
    else{
        p->value.number = value.number;
        p->type = NUMBER;
    }

    p->next = next;

    return p;
}

/**
 * Delete Pair structure.
 * @param   p               Pair structure.
 * @param   recursive       Whether or not to delete remainder of pairs.
 * return   NULL.
 */
Pair *	    pair_delete(Pair *p, bool recursive) {
    if(p == NULL)
        return NULL;

    if(recursive){
        pair_delete(p->next, recursive);
    }

    if(p->type == STRING){
        free(p->value.string);
    }
    
    free(p->key);
    free(p);

    return NULL;
}

/**
 * Update Pair's value.
 * @param   p               Pair structure.
 * @param   value           New value for Pair.
 * @param   type            New value's type.
 */
void        pair_update(Pair *p, const Value value, Type type) {
    if(p->type == STRING){
        free(p->value.string);
    }

    if(type == STRING){
        p->value.string = strdup(value.string);
        p->type = STRING;
    }

    else{
         p->value.number = value.number;
         p->type = NUMBER;
    }
}

/**
 * Format Pair by writing to stream.
 * @param   p               Pair structure.
 * @param   stream          File stream to write to.
 */
void        pair_format(Pair *p, FILE *stream) {
    if(p->type == STRING){
        fprintf(stream, "%s\t%s\n", p->key, p->value.string);
    }

    if(p->type == NUMBER){
        fprintf(stream, "%s\t%ld\n", p->key, p->value.number);    
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
