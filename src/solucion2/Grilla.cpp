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

//nodos
Nodo* Grilla::createNode(uchar* palabra){
  Nodo* nuevo = new Nodo;

  nuevo->key = copyString(palabra);

  nuevo->netx = nullptr;
  nuevo->prev = nullptr;
  nuevo->down = nullptr;

  return nuevo;
}

//insertar
bool Grilla::insert(uchar* palabra){
  Nodo* nuevo = createNode(palabra);
  //lista vacía
  if(head == nullptr){
    head = nuevo;
    return true;
  }
  //insertar al inicio
  if(compare(palabra, head->key) < 0){
    nuevo->next = head;
    head->prev = nuevo;
    head = nuevo;
    return true;
  }
  Nodo* p = head;
  while(p->next != nullptr &&
  compare(p->next->key, palabra) < 0){
    p = p->next;
  }
  //palabra repetida
  if(compare(p->key, palabra) == 0){
    delete[] nuevo->key;
    delete nuevo;
    return false;
  }
  if(p->next != nullptr &&
    compare(p->next->key, palabra) == 0){
      delete[] nuevo->key;
      delete nuevo; 
      return false;
  }
  nuevo->next = p->next;
  if(p->next != nullptr)
    p->next->prev = nuevo;
  nuevo->prev = p;
  p->next = nuevo;
  return true;
}
