CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/thor

# -----------------------------------------------------------------------------

all:		$(TARGETS)

# TODO: Add rules for lib/libthor.a, bin/unit_{timestamp,socket,request,hammer},
# bin/thor and any objects they require

# -----------------------------------------------------------------------------

tests/unit_hammer.o: tests/unit_hammer.c
	$(CC) $(CFLAGS) -c -o tests/unit_hammer.o tests/unit_hammer.c

bin/unit_hammer: tests/unit_hammer.o lib/libthor.a
	$(LD) $(LDFLAGS) -o bin/unit_hammer tests/unit_hammer.o -lthor

tests/unit_request.o: tests/unit_request.c
	$(CC) $(CFLAGS) -c -o tests/unit_request.o tests/unit_request.c

bin/unit_request: tests/unit_request.o lib/libthor.a
	$(LD) $(LDFLAGS) -o bin/unit_request tests/unit_request.o -lthor

tests/unit_socket.o: tests/unit_socket.c
	$(CC) $(CFLAGS) -c -o tests/unit_socket.o tests/unit_socket.c

bin/unit_socket: tests/unit_socket.o lib/libthor.a
	$(LD) $(LDFLAGS) -o bin/unit_socket tests/unit_socket.o -lthor

tests/unit_timestamp.o: tests/unit_timestamp.c
	$(CC) $(CFLAGS) -c -o tests/unit_timestamp.o tests/unit_timestamp.c

bin/unit_timestamp: tests/unit_timestamp.o lib/libthor.a
	$(LD) $(LDFLAGS) -o bin/unit_timestamp tests/unit_timestamp.o -lthor

src/thor.o: src/thor.c
	$(CC) $(CFLAGS) -c -o src/thor.o src/thor.c

bin/thor: src/thor.o lib/libthor.a
	$(LD) $(LDFLAGS) -o bin/thor src/thor.o -lthor

src/hammer.o: src/hammer.c
	$(CC) $(CFLAGS) -c -o src/hammer.o src/hammer.c

src/request.o: src/request.c
	$(CC) $(CFLAGS) -c -o src/request.o src/request.c

src/socket.o: src/socket.c
	$(CC) $(CFLAGS) -c -o src/socket.o src/socket.c

src/timestamp.o: src/timestamp.c
	$(CC) $(CFLAGS) -c -o src/timestamp.o src/timestamp.c

lib/libthor.a: src/hammer.o src/request.o src/socket.o src/timestamp.o 
	$(AR) $(ARFLAGS) -o lib/libthor.a src/hammer.o src/request.o src/socket.o src/timestamp.o

# test

test:
	@$(MAKE) -sk test-all

test-all:               test-timestamp test-socket test-request test-hammer test-thor

test-timestamp:		bin/unit_timestamp
	@bin/test_timestamp.sh

test-socket:		bin/unit_socket
	@bin/test_socket.sh

test-request:		bin/unit_request
	@bin/test_request.sh

test-hammer:		bin/unit_hammer
	@bin/test_hammer.sh

test-thor:		bin/thor
	@bin/test_thor.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_* lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
