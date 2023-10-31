CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
LIBS=		-lcrypto
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/duplicates

all:		$(TARGETS)

# TODO: Add rules for bin/unit_hash, bin/unit_pair, bin/unit_table, bin/duplicates

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

lib/libtable.a: src/hash.o src/pair.o src/table.o
	$(AR) $(ARFLAGS) $@ $^

bin/unit_%: tests/unit_%.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/duplicates: src/duplicates.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

test:
	@$(MAKE) -sk test-all

test-all:               test-hash test-pair test-table test-duplicates

test-pair:		bin/unit_pair
	@bin/test_pair.sh

test-hash:		bin/unit_hash
	@bin/test_hash.sh

test-table:		bin/unit_table
	@bin/test_table.sh

test-duplicates:	bin/test_duplicates.sh bin/duplicates
	@bin/test_duplicates.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_pair bin/unit_hash bin/unit_table lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
