CC=cc
CFLAGS=$$(pkg-config --cflags ncurses)
CFLAGS+=-O2
LIBS=$$(pkg-config --libs ncurses)

PREFIX?=/usr/local
PROGNAME=greentext

SOURCES=src

.PHONY: install clean

$(PROGNAME): main.o streak.o util.o
	$(CC) main.o streak.o util.o -o $(PROGNAME) $(LIBS)
	strip $(PROGNAME)

main.o: $(SOURCES)/main.c
	$(CC) $(CFLAGS) -c $(SOURCES)/main.c

streak.o: $(SOURCES)/streak.c
	$(CC) $(CFLAGS) -c $(SOURCES)/streak.c

util.o: $(SOURCES)/util.c
	$(CC) $(CFLAGS) -c $(SOURCES)/util.c

install: greentext
	cp $(PROGNAME) $(PREFIX)/bin

clean:
	rm -f *.o
