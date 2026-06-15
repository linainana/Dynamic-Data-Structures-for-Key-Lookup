CC=g++
CFLAGS=-Wall -std=c++17 -O3

TARGET = grilla

OBJS = main2.o Grilla.o Funciones.o
all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


main2.o: main2.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c main2.cpp

Grilla.o: Grilla.cpp Grilla.h Funciones.h
	$(CC) $(CFLAGS) -c Grilla.cpp

Funciones.o: Funciones.cpp Funciones.h
	$(CC) $(CFLAGS) -c Funciones.cpp


clean:
	@echo " [CLN] Eliminando ejecutables y archivos objeto temporales..."
	@rm -f $(TARGET) $(OBJS)
