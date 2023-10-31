/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 **/
void str_lower(char *s) {
    char *strptr = s;
    // looping until NULL 
    while(*strptr != '\0'){
        *strptr = tolower(*strptr);
        strptr++;
    }
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 **/
void str_upper(char *s) {
    // same concept as above
    char *strptr = s;
    while(*strptr != '\0'){
        *strptr = toupper(*strptr);
        strptr++;
    }
        
}

/**
 * Convert all characters in string to titlecase.
 * @param   s       String to convert
 **/
void str_title(char *s) {
    // converting to title case, so that if is alpha then uppercase
    if(isalpha(*s)){
        *s = toupper(*s);
    }
    /*while(*s != '\0'){
        *s = toupper(*s);
        s++;
    }*/

    char *strptr = s;
    while(*(strptr + 1)){
        if(!isalpha(*strptr) && isalpha(*(strptr + 1))){
            *(strptr + 1) = toupper(*(strptr + 1));
        }
        else if(isalpha(*(strptr + 1))){
            *(strptr + 1) = tolower(*(strptr + 1));
        }
        strptr++;
    }
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 **/
void str_chomp(char *s) {
    char *strptr = s;
    while(*strptr != '\0'){
        if(*(strptr + 1) == '\0' && *strptr == '\n'){
            *strptr = '\0';    
        }
        strptr++;
    }
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 **/
void str_strip(char *s) {
    char *param1 = s;
    char *param2 = s;

    while(isspace(*param1)){
        param1++;
    }
    while(*param1){
        *param2 = *param1;
        param1++;
        param2++;
    }
    // null reset
    *param2 = '\0';
    param2--;

    while(isspace(*param2)){
        *param2 = '\0';
        param2--;
    }
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 **/
 // inspiration from geeksforgeeks * credit
void str_reverse(char *s) {
    char *head = s;
    char *tail = s + strlen(s) - 1;

    while(head < tail){
        char tempnode = *head;
        *head = *tail;
        *tail = tempnode;
        head++;
        tail--;
    }
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 **/
void str_translate(char *s, char *from, char *to) {
    int table[1<<8] = {0};
    for(char *i = from; *i; i++, to++){
        table[(int)*i] = *to;
    }
    for(char *i = s; *i; i++){
        if(table[(int)*i] != 0){
            *i = table[(int)*i];
        }
    }   
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
