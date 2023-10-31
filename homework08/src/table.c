/* table.c: Separate Chaining Hash Table */

#include "table.h"
#include "hash.h"
#include "macros.h"

/**
 * Create Table data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @return  Allocated Table structure.
 */
Table *	    table_create(size_t capacity) {
    Table *t = malloc(sizeof(Table));
    if(t == NULL)
        return NULL;
    if(capacity == 0)
        capacity = DEFAULT_CAPACITY;

    t->capacity = capacity;
    t->size = 0;
    t->buckets = calloc(capacity, sizeof(Pair));
    if (t->buckets == NULL)
        return NULL;

    return t;
}

/**
 * Delete Table data structure.
 * @param   t               Table data structure.
 * @return  NULL.
 */
Table *	    table_delete(Table *t) {
    for(Pair *p = t->buckets; p < t->buckets + t->capacity; p++){
        if(p){
            pair_delete(p->next, true);
        }
    }

    free(t->buckets);
    free(t);

    return NULL;
}

/**
 * Insert or update Pair into Table data structure.
 * @param   m               Table data structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   type            Pair's value's type.
 */
void        table_insert(Table *t, const char *key, const Value value, Type type) {
    size_t number = strlen(key) % 8 ? strlen(key)/8+1 : strlen(key);
    int bucket = hash_from_data(key, number) % t->capacity;

    Pair *current = t->buckets + bucket;

    while (current->next){
        if (streq(key, current->next->key)){
            pair_update(current->next, value, type);
            return;
        }
        current = current->next;
    }
    
    Pair *p = pair_create(key, value, NULL, type);
    current->next = p;

    t->size++;
}

/**
 * Search Table data structure by key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to search for.
 * @return  Pointer to the Value associated with specified key (or NULL if not found).
 */
Value *     table_search(Table *t, const char *key) {
    size_t number = strlen(key) % 8 ? strlen(key)/8+1 : strlen(key);
    int bucket = hash_from_data(key, number) % t->capacity;

    Pair *current = t->buckets[bucket].next;
    while(current){
        if(streq(key, current->key)){
             return &current -> value;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * Remove Pair from Table data structure with specified key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to remove.
 * return   Whether or not the removal was successful.
 */
bool        table_remove(Table *t, const char *key) {
    size_t number = strlen(key) % 8 ? strlen(key)/8+1 : strlen(key);
    int bucket = hash_from_data(key, number) % t->capacity;

    Pair *previous = t->buckets + bucket;
    for(Pair *current = previous->next; current; current = current->next){
        if(streq(key, current->key)){
            previous->next = current->next;
            pair_delete(current, false);
            t->size--;
            return true;
        }
        previous = current;
    }   
    return false;
}

/**
 * Format all the entries in the Table data structure.
 * @param   m               Table data structure.
 * @param   stream          File stream to write to.
 */
void	    table_format(Table *t, FILE *stream) {
    for(Pair *p = t->buckets; p < t->buckets + t->capacity; p++){
        for(Pair *q = p->next; q; q = q->next){
            pair_format(q, stream);
        }
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
