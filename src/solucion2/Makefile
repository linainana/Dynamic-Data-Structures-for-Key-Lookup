CC=g++
CFLAGS=-Wall -std=c++17 -O3
BINS=grilla main2.o Grilla.o Funciones.o

all: clean grilla

grilla: main2.o Grilla.o Funciones.o
	$(CC) $(CFLAGS) -o grilla main2.o Grilla.o Funciones.o

main2.o: main2.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c main2.cpp

Grilla.o: Grilla.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c Grilla.cpp

Funciones.o: Funciones.cpp Funciones.h
	$(CC) $(CFLAGS) -c Funciones.cpp

clean:
	@echo " [CLN] Removing binary files :))"
	@rm -f $(BINS)

