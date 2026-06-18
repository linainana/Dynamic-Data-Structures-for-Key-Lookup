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

class Grilla{
public:
   Nodo* head;
   int levels;
   int k;

   //constructor y destructor
   Grilla(int K);
   virtual ~Grilla();

   //operaciones principales
   bool insert(uchar* palabra);
   Nodo* search(uchar* palabra);
   bool remove(uchar* palabra);

   //impresión
   void printLevel(Nodo* l);
   void printGrid();

   //manejo de nodos
   Nodo* createNode(uchar* palabra);
   void deleteLevels(Nodo* l);

   //niveles
   int sizeLevel(Nodo* l);
   Nodo* buildUpperLevel(Nodo* lower);
   void rebuildGrid();
   void deleteUpperLevels(); 
   int memoria_usada();
};
#endif
