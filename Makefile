CC=cc
CCFLAGS=-O2
LIBS=-lncurses -ltinfo

PREFIX?=/usr/local

.PHONY: install clean

greentext: src/main.c
	$(CC) $(CCFLAGS) src/main.c -o greentext $(LIBS)

install: greentext
	cp greentext $(PREFIX)/bin

clean:
	rm greentext
