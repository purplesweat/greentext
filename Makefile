CC=cc
CFLAGS=$$(pkg-config --cflags ncurses)
CFLAGS+=-O2
LIBS=$$(pkg-config --libs ncurses)

PREFIX?=/usr/local
PROGNAME=greentext

.PHONY: install clean

$(PROGNAME): src/main.c
	$(CC) $(CFLAGS) src/main.c -o $(PROGNAME) $(LIBS)
	strip $(PROGNAME)

install: greentext
	cp $(PROGNAME) $(PREFIX)/bin

clean:
	rm -f $(PROGNAME)
