#include "Funciones.h"

int length(uchar* s){
  int i = 0;
  while(s[i] != '\0')
    i++;
  return i;
}

int compare(uchar* a, uchar* b){
  int i = 0;
  while(a[i] != '\0' && b[i] != '\0'){
    if(a[i] < b[i])
      return -1;
    if(a[i] > b[i])
      return 1;
    i++;
  }
  if(a[i] == '\0' && b[i] == '\0')
    return 0;
  if(a[i] == '\0')
    return -1;
  return 1;
}

uchar* copyString(uchar* s){
  int n = length(s);
  uchar* copia = new uchar[n + 1];
  for(int i=0; i<n; i++)
    copia[i] = s[i];
  copia[n] = '\0';
  return copia;
}

void cleanLine(uchar* s){
  int i = 0;
  while(s[i] != '\0'){
    if(s[i] == '\n' || s[i] == '\r'){
      s[i] = '\0';
      return;
    }
    i++;
  }
}

uchar* readWord(ifstream& file){
  char buffer[256];
  while (file.getline(buffer, 256)){ 
    int n = 0;
    while(buffer[n] != '\0'){
      if (buffer[n] == '\r' || buffer[n] == '\n'){
        buffer[n] = '\0';
        break;
      }
      n++;
    }
    if(n > 0){
      uchar* palabra = new uchar[n + 1];
      for(int i=0; i<n; i++)
        palabra[i] = (uchar) buffer[i];
      palabra[n] = '\0';
      return palabra;
    }
  }
  return nullptr;
}

void desordenarPalabras(uchar** arreglo, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uchar* tmp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = tmp;
    }
}
