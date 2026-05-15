#include "Grilla.h"
#include "Funciones.h" 

Grilla::Grilla(int K){
  head = nullptr;
  evels = 1;
  k = K;
}

Grilla::~Grilla(){
  deleteLevels(head);
}
//nodo
Nodo* Grilla::createNode(uchar* palabra){
  Nodo* nuevo = new Nodo;

  nuevo->key = copyString(palabra);

  nuevo->netx = nullptr;
  nuevo->prev = nullptr;
  nuevo->down = nullptr;

  return nuevo;
}
