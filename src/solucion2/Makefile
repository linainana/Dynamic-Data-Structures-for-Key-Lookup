CC=g++
CFLAGS=-Wall -std=c++17 -O3
# Aquí en BINS pones el nombre del ejecutable y los archivos objeto .o
BINS=grilla main2.o Grilla.o Funciones.o

all: clean grilla

# Regla final: une todos los .o para crear el ejecutable 'grilla'
grilla: main2.o Grilla.o Funciones.o
	$(CC) $(CFLAGS) -o grilla main2.o Grilla.o Funciones.o

# Compila el main
main2.o: main2.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c main2.cpp

# Compila la clase Grilla
Grilla.o: Grilla.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c Grilla.cpp

# Compila las funciones auxiliares
Funciones.o: Funciones.cpp Funciones.h
	$(CC) $(CFLAGS) -c Funciones.cpp

clean:
	@echo " [CLN] Removing binary files :))"
	@rm -f $(BINS)

