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
