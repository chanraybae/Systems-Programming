/* str_title: convert strings to title-case */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_title(const char *s) {
    char *t = strdup(s);
    char *c = t;
    while (*c) {
      *c = toupper(*c);
      while (*c && !isspace(*c++));
    }

    return t;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i <= argc; i++) {
      if(i < argc){	
		char *t = str_title(argv[i]);
      	puts(t);
		free(t);
	  }
    }
    return 0;
}
