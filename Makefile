CC=gcc
CFLAGS=-pipe -ggdb

all: Simulator.o
	$(CC) $(CFLAGS) Simulator.o -o Simulator

Simulator.o: Simulator.c
	$(CC) $(CFLAGS) -c Simulator.c

clean:
	rm Simulator *.o *.*~ *~




