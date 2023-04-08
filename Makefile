CC=cc
CCFLAGS=-O2
LIBPATHS=
LIBS=-lncurses

PREFIX?=/usr/local

.PHONY: install

greentext: src/main.c
	cc $(CCFLAGS) src/main.c -o greentext $(LIBS)

install: greentext
	cp greentext $(PREFIX)/bin