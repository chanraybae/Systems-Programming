/* hash.c: hash functions */

#include "hash.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <openssl/md5.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 */

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   data            Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash as 64-bit unsigned integer.
 */
uint64_t    hash_from_data(const void *data, size_t n) {
    uint64_t hashed = FNV_OFFSET_BASIS;
    uint8_t *bytes = (uint8_t *) data;

    for(size_t i = 0; i < n; i++){
        hashed = hashed ^ bytes[i];
        hashed = hashed * FNV_PRIME;
    }
    
    return hashed;
}

/**
 * Compute MD5 digest.
 * @param   path            Path to file to checksum.
 * @param   hexdigest       Where to store the computed checksum in hexadecimal.
 * @return  Whether or not the computation was successful.
 */
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]) {
    MD5_CTX context;
    MD5_Init(&context);

    FILE *stream = fopen(path, "r");
    if (!stream){
        fprintf(stderr, "fopen failed on %s: %s\n", path, strerror(errno));
        return false;
    }

    char buffer[BUFSIZ];
    size_t nread;

    while ((nread = fread(buffer, 1, BUFSIZ, stream)) > 0){
        MD5_Update(&context, buffer, nread);
    }

    fclose(stream);

    unsigned char rawdigest[MD5_DIGEST_LENGTH];
    MD5_Final(rawdigest, &context);

    for (size_t i = 0; i < MD5_DIGEST_LENGTH; i++){
        sprintf(hexdigest + i*2, "%02x", rawdigest[i]);
    }

    return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
