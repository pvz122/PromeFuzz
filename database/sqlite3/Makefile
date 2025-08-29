CC ?= gcc
AR ?= ar
CFLAGS ?= -O2 -fPIC
INSTALL_PREFIX ?= /usr/local

all: libsqlite3.a

libsqlite3.a: sqlite3.o
	$(AR) rcs $@ $^

sqlite3.o: sqlite3.c
	$(CC) $(CFLAGS) -c $< -o $@

install: libsqlite3.a sqlite3.h
	install -d $(INSTALL_PREFIX)/lib $(INSTALL_PREFIX)/include
	install -m 644 libsqlite3.a $(INSTALL_PREFIX)/lib/
	install -m 644 sqlite3.h $(INSTALL_PREFIX)/include/
	install -m 644 sqlite3ext.h $(INSTALL_PREFIX)/include/

clean:
	rm -f sqlite3.o libsqlite3.a
