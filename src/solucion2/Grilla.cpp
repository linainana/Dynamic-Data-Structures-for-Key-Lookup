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

//buscar
Nodo* Grilla::search(uchar* palabra){
  Nodo* p = head;
  while(p != nullptr){
    while(p->next != nullptr && compare(p->next->key, palabra) <= 0){
      p = p->next;
    }
    if(compare(p->key, palabra) == 0)
      return p;
    p = p->down;
  }
  return nullptr;
}

//eliminar 

bool Grilla::remove(uchar* palabra){
//bajar hasta el nivel base (L1)
  Nodo* base = head;
  if(base == nullptr) return false;
  while(base->down != nullptr) base = base->down;
  //buscar la palbra en el nivel base (recorrido lineal)
  Nodo* p = base;
  while(p != nullptr && commpare(p->key, palabra) 1= 0){
    p = p->next;
  }
  //si no se encuentra, no hay nada que eliminar 
  if(p == nullptr) return false;
 
  //desconectar el nodo de la lista doblemente enlazada (L1)
  if(p->prev != nullptr){
     p->prev->next = p->prev;
  } else {
     //si era el primero, el nuevo inicio de la base es el siguiente
     base = p->next;
  }

  if(p->next != nullptr){
     p->next->prev = p->prev;
  }

  //liberar la memoria del nodo eliminado en L1
  delete[] p->key;
  delete p;

  //saneanmiento y actualización de la grilla 
  //borramos los índices viejos que ya no son validos 
  deleteUpperLevels();

  //ahora 'head' apunta al inicio de L1
  //reconsttruimos los niveles superiores para mantener la eficiencia de búsqueda
  rebuindGrid();

  return true;
}
