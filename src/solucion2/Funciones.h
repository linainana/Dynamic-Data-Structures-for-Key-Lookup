#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef unsigned char uchar;

//utilidades para manejo de cadenas
int length(uchar* s); 
int compare(uchar* a, uchar* b); 
uchar* copyString(uchar* s); 

//utilidades para lectura y procesamiento de archivos
void cleanLine(uchar* s);
void desordenarPalabras(uchar** arreglo, int n);
uchar* readWord(ifstream& file); 

#endif
