# Variables de compilación
CC = g++
CFLAGS = -Wall -std=c++17 -O3

# Nombre de los ejecutables y archivos objeto
BINS = arreglo_dinamico grilla
OBJS = main2.o Grilla.o Funciones.o

# Regla por defecto (compila ambos programas)
all: clean $(BINS)

# Regla para compilar el programa del Arreglo Dinámico (main1)
arreglo_dinamico: main1.cpp
	$(CC) $(CFLAGS) -o arreglo_dinamico main1.cpp

# Regla para compilar el programa de la Grilla (main2)
grilla: $(OBJS)
	$(CC) $(CFLAGS) -o grilla $(OBJS)

# Reglas de compilación para los archivos objeto individuales
main2.o: main2.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c main2.cpp

Grilla.o: Grilla.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c Grilla.cpp

Funciones.o: Funciones.cpp Funciones.h
	$(CC) $(CFLAGS) -c Funciones.cpp

# Limpieza de binarios y archivos objeto
clean:
	@echo " [CLN] Limpiando archivos binarios y objetos..."
	@rm -f $(BINS) $(OBJS)
