CC=gcc

CFLAGS=-g -Wall -pedantic -D_GNU_SOURCE=1 -D_REENTRANT
SOURCES=main.c utils.c
OBJECTS=main.o utils.o
BINARIES=main

all: $(BINARIES)

main: main.o utils.o
	$(CC) -o forca main.o utils.o

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)
	
clean:
	rm -rf *.o *.exe *.bak *.c~ $(BINARIES) core a.out


