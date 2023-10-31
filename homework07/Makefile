CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -fPIC -std=c99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstr.a \
		libstr.so

all:		$(TARGETS)

test:		
	@$(MAKE) -sk test-all
	
test-all:	test-libstr test-str

test-libstr:	libstr.so
	curl -sLO https://raw.githubusercontent.com/nd-cse-20289-sp22/cse-20289-sp22-assignments/master/homework07/test_libstr.py
	chmod +x test_libstr.py
	./test_libstr.py -v

test-str:	str-static str-dynamic
	curl -sLO https://raw.githubusercontent.com/nd-cse-20289-sp22/cse-20289-sp22-assignments/master/homework07/test_str.sh
	chmod +x test_str.sh
	./test_str.sh

clean:
	rm -f $(TARGETS) *.o

# TODO: Add rules for libstr.a libstr.so
library.o: library.c
	$(CC) $(CFLAGS) -c -o library.o library.c

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

libstr.a: library.o
	$(AR) $(ARFLAGS) libstr.a library.o

libstr.so: library.o
	$(CC) $(LDFLAGS) -shared -o libstr.so library.o

# TODO: Add rules for str-dynamic str-static
str-static: main.o libstr.a
	$(LD) $(LDFLAGS) -static -o str-static main.o -lstr

str-dynamic: main.o libstr.so
	$(LD) $(LDFLAGS) -o str-dynamic main.o -lstr
