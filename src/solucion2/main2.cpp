#include "Grilla.h"
#include "Funciones.h"
#include <chrono> //para medir tiempos

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
  if(argc != 3){
    cout << "Modo de uso: ./main D1.txt k" << endl;
    return 0;
  }
  int k = atoi(argv[2]);
  Grilla g(k);

  //medición de inserción y construcción
  ifstream file(argv[1]);
  if(!file.is_open()){
    cout << "No se pudo abrir archivo" << endl;
    return 0;
  }

  auto start_const = high_resolution_clock::now();
  while(true){
    uchar* palabra = readWord(file);
    if(palabra == nullptr) break; 
    if(length(palabra) > 0) {
        g.insert(palabra);
    }
    delete[] palabra; 
}
  file.close();
  g.rebuildGrid(); //parte de la construcción de la estructura
  auto end_const = high_resolution_clock::now();
  duration<double> t_const = end_const - start_const;
  cout << "Tiempo de Construcción total: " << t_const.count() << " segundos" << endl;

  //medición de búsqueda
  char buffer[256];
  cout << "\nIngrese palabra a buscar: ";
  cin >> buffer;
  uchar* buscar = (uchar*) buffer;
  auto start_search = high_resolution_clock::now();
  Nodo* res_s = g.search(buscar);
  auto end_search = high_resolution_clock::now();
  duration<double> t_search = end_search - start_search;
  if(res_s) cout << "Palabra encontrada. ";
  else cout << "Palabra no encontrada. ";
  cout << "Tiempo de búsqueda: " << t_search.count() << " segundos" << endl;

  //medición de eliminación
  cout << "\nIngrese palabra a eliminar: ";
  cin >> buffer;
  uchar* eliminar = (uchar*) buffer;
  auto start_remove = high_resolution_clock::now();
  bool rem = g.remove(eliminar);
  auto end_remove = high_resolution_clock::now();
  duration<double> t_remove = end_remove - start_remove;
  if(rem) cout << "Palabra eliminada. ";
  else cout << "Palabra no encontrada. ";
  cout << "Tiempo de eliminación (con reconstrucción): " << t_remove.count() << " segundos" << endl;

  return 0;
}

