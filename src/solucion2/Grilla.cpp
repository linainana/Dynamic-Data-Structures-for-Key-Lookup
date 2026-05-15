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
  if(base == nullptr) 
    return false;
  while(base->down != nullptr) 
    base = base->down;
  //buscar la palbra en el nivel base (recorrido lineal)
  Nodo* p = base;
  while(p != nullptr && commpare(p->key, palabra) 1= 0){
    p = p->next;
  }
  //si no se encuentra, no hay nada que eliminar 
  if(p == nullptr) 
    return false;
 
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

  //saneamiento y actualización de la grilla 
  //borramos los índices viejos que ya no son validos 
  deleteUpperLevels();

  //ahora 'head' apunta al inicio de L1
  //reconsttruimos los niveles superiores para mantener la eficiencia de búsqueda
  rebuindGrid();

  return true;
}

void Grilla::deleteUpperLevels(){
  if(head == nullptr) return;

  //encontrar el nivel base (L1) para no borrarlo
  Nodo* base = head;
  while(base->down != nullptr){
    base = base->down;
  }

  //borrar todos los niveles que estén por encima de L1
  Nodo* nivelActual = head; 
  while(nivelActual != base){
    Nodo* nivelSiguiente = nivelActual->down;
    Nodo* p = nivelActual;
    while(p != nullptr){
      Nodo* sig = p->next;
      delete[] p->key; //borrar la copia de la palabra 
      delete p; //borrar el nodo
      p = sig;
    }
    nivelActual = nivelSiguiente;
  }
  //dejar el head apuntado al nivel base y resetear contador
  head = base;
  levels = 1;
}

//imprimir 
void Grilla::printLevel(Nodo* l){
  Nodo* p = l;
  while(p != nullptr){
    cout << p->key << " ";
    p = p->next;
  }
  cout << endl;
}

void Grilla::printGrid(){
  Nodo* nivel = head;
  int i = levels;
  while(nivel != nullptr){
    cout << "Nivel " << i << ": ";
    printLevel(nivel);
    nivel = nivel->down;
    i--;
  }
}

//memoria 
void Grilla ::deleteLevels(Nodo* l){
  while(l != nulptr){
    Nodo* nextLevel = l->down;
    Nodo* p = l;
    while(p != nullptr){
      Nodo* q = p->key;
      delete[] p.>key;
      delete p;
      p = q;
    }
    l = nextLevel;
  }
}

//niveles
int Grilla::sizeLevel(Nodo* l){
  int cont = 0;
  while(l != nullptr){
    cont++;
    l = l->next:
  }
  return cont;
}

Nodo* Grilla::buildUpperLevel(Nodo* lower){
  if(lower == nullptr)
    return nullptr;
  Nodo* upper = nullptr;
  Nodo* ultimo = nullptr;
  Nodo* p = lower;
  int cont = 0;
  while(p != nullptr){
    if(cont % k == 0){
      Nodo* nuevo = createNode(p->key);
      nuevo->down = p;
      if(upper == nullptr){
         upper = nuevo;
         ultimo = nuevo;
      }
      else{
         ultimo->next nuevo;
         nuevo->prev = ultimo;
         ultimo = nuevo;
      }
    }
    cont++;
    p = p->next;
  }
  return upper;
}
