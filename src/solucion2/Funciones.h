#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef unsigned char uchar;

//funnciones para uchar*
int length(uchar* s); //largo de una palabra
int compare(uchar* a, uchar* b); //compara lexicográficamente
//retorna -1 si a<b, 0 si a==b, 1 si a>b
uchar* copyString(uchar* s); //copia una palabra 

//archivos
void cleanLine(uchar* s); //elimina salto de línea
uchar* readWord(ifstream& file); //lee una palabra desde archivo
#endif
