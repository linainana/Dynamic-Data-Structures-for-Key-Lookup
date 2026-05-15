#includ "Funciones.h"

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
  if(a[i] == '\0' && b[] == '\0')
    return 0;
  if(a[i] == '\0')
    return -1;
  return 1;
}
