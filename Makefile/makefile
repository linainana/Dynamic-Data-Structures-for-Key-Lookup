#Variables de compilación
CC = g++
CFLAGS = -Wall -std=c++17 -O3

#Rutas de las carpetas
DIR_SOL1 = ../src/solucion1
DIR_SOL2 = ../src/solucion2
DIR_SOL3 = ../src/solucion3
DIR_DATA = ../data

BINS = arreglo_dinamico grilla kario

all: clean $(BINS)

#Regla para compilar la solución 1 (arreglo dinámico)
arreglo_dinamico: $(DIR_SOL1)/main1.cpp
	$(CC) $(CFLAGS) -o arreglo_dinamico $(DIR_SOL1)/main1.cpp

#Regla para compilar la solución 2 (grilla) 
grilla: main2.o Grilla.o Funciones.o
	$(CC) $(CFLAGS) -o grilla main2.o Grilla.o Funciones.o

#Compilación de objetos intermedios buscando los archivos dentro de src/solucion2
main2.o: $(DIR_SOL2)/main2.cpp $(DIR_SOL2)/Grilla.h $(DIR_SOL2)/Funciones.h
	$(CC) $(CFLAGS) -c $(DIR_SOL2)/main2.cpp

Grilla.o: $(DIR_SOL2)/Grilla.cpp $(DIR_SOL2)/Grilla.h $(DIR_SOL2)/Funciones.h
	$(CC) $(CFLAGS) -c $(DIR_SOL2)/Grilla.cpp

Funciones.o: $(DIR_SOL2)/Funciones.cpp $(DIR_SOL2)/Funciones.h
	$(CC) $(CFLAGS) -c $(DIR_SOL2)/Funciones.cpp

kario: $(DIR_SOL3)/main3.cpp
	$(CC) $(CFLAGS) -o kario $(DIR_SOL3)/main3.cpp

run: $(BINS)
	@echo "CORRIENDO EXPERIMENTO 1: ARREGLO DINÁMICO"
	./arreglo_dinamico $(DIR_DATA)/d1.txt $(DIR_DATA)/d2.txt 0.5
	@echo "CORRIENDO EXPERIMENTO 2: GRILLA"
	./grilla $(DIR_DATA)/d1.txt $(DIR_DATA)/d2.txt 32
	@echo "CORRIENDO EXPERIMENTO 3: ÁRBOL K-ARIO"
	./kario $(DIR_DATA)/d1.txt $(DIR_DATA)/d2.txt

#Limpieza total de binarios y archivos objeto intermedios
clean:
	@echo "Limpiando ejecutables y archivos objeto..."
	@rm -f $(BINS) *.o
