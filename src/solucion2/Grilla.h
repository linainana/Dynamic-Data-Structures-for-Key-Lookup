#ifndef GRILLA_H
#define GRILLA_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef unsigned char uchar;

struct nodoGrilla{
   uchar* key; //palabra almacenada

   nodoGrilla* next; //siguiente nodo mismo nivel
   nodoGrilla* prev; //nodo anterior mismo nivel
   nodoGrilla* down; //mismo nodo en nivel inferior 
};
typedef struct nodoGrilla Nodo;
