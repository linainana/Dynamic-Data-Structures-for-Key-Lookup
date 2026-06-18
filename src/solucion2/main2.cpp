#include "Grilla.h"
#include "Funciones.h"
#include <chrono> //para medir tiempos

using namespace std;
using namespace std::chrono;
#include "Grilla.h"
#include "Funciones.h"
#include <chrono> //para medir tiempos

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
  if(argc != 4){#include "Grilla.h"
#include "Funciones.h"
#include <chrono> //para medir tiempos

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
  if(argc != 4){
    cout << "Modo de uso: ./grilla data/d1.txt data/d2.txt k" << endl;
    return 0;
  }

  srand(42);

  int k = atoi(argv[3]);
  Grilla g(k);

  //medición de inserción y construcción D1
  ifstream filed1(argv[1]);
  if(!filed1.is_open()){
    cout << "No se pudo abrir el archivo D1" << endl;
    return 0;
  }

  auto start_const = high_resolution_clock::now();
  while(true){
    uchar* palabra = readWord(filed1);
    if(palabra == nullptr) break; 
    if(length(palabra) > 0) {
        g.insert(palabra);
    }
    delete[] palabra; 
}
  filed1.close();
  g.rebuildGrid(); //parte de la construcción de la estructura

  auto end_const = high_resolution_clock::now();
  duration<double> t_const = end_const - start_const;

  cout << "Tiempo de Construcción inicial D1: " << t_const.count() << " segundos" << endl;
  cout << "Memoria usada: " << g.memoria_usada() << " bytes." << endl;

  //medición de inserción y construcción D1
  ifstream filed2(argv[2]);
  if(!filed2.is_open()){
    cout << "No se pudo abrir el archivo D2" << endl;
    return 0;
  }

  //reservar espacio
  uchar* lote_d2[10000];
  int total_d2 = 0;

  while(total_d2 < 10000){
    uchar* palabra = readWord(filed2);
    if(palabra == nullptr) break;
    if(length(palabra) > 0){
      lote_d2[total_d2] = palabra;
      total_d2++;
    } else {
      delete[] palabra;
    }
  }
  filed2.close();

  desordenarPalabras(lote_d2, total_d2);

  //búsqueda masiva
  int encontradas = 0;
  auto start_search = high_resolution_clock::now();
  
  for(int i = 0; i < total_d2; i++){
    if(g.search(lote_d2[i]) != nullptr) {
        encontradas++;
    }
  }
  
  auto end_search = high_resolution_clock::now();
  duration<double> t_search = end_search - start_search;

  cout << "Palabras encontradas exitosamente: " << encontradas << " de " << total_d2 << endl;
  cout << "Tiempo total de busqueda: " << t_search.count() << " segundos." << endl;
  cout << "Tiempo promedio por palabra: " << (t_search.count() / total_d2) << " segundos." << endl;

  //inserción masiva
  int n_insertar = (total_d2 < 5000) ? total_d2 : 5000;
  int inserciones_exitosas = 0;
  
  auto start_insert = high_resolution_clock::now();
  for(int i = 0; i < n_insertar; i++){
    if(g.insert(lote_d2[i])) {        // Intentamos re-insertar en la estructura
        inserciones_exitosas++;
    }
  }

  g.rebuildGrid();
  auto end_insert = high_resolution_clock::now();
  duration<double> t_insert = end_insert - start_insert;

  cout << "Inserciones nuevas realizadas: " << inserciones_exitosas << " de " << n_insertar << " intentadas." << endl;
  cout << "Tiempo total de insercion: " << t_insert.count() << " segundos." << endl;

  //eliminación masiva
  int eliminaciones_exitosas = 0;
  
  auto start_remove = high_resolution_clock::now();
  for(int i = 0; i < n_insertar; i++){
    if(g.remove(lote_d2[i])) {
        eliminaciones_exitosas++;
    }
  }
  
  auto end_remove = high_resolution_clock::now();
  duration<double> t_remove = end_remove - start_remove;

  cout << "Eliminaciones exitosas: " << eliminaciones_exitosas << " de " << n_insertar << " intentadas." << endl;
  cout << "Tiempo total de eliminacion: " << t_remove.count() << " segundos." << endl;

  for(int i = 0; i < total_d2; i++) {  //limpieza final de la memoria dinámica usada para pruebas
      delete[] lote_d2[i];
  }

  return 0;
}


    cout << "Modo de uso: ./grilla data/d1.txt data/d2.txt k" << endl;
    return 0;
  }

  srand(42);

  int k = atoi(argv[3]);
  Grilla g(k);

  //medición de inserción y construcción D1
  ifstream filed1(argv[1]);
  if(!filed1.is_open()){
    cout << "No se pudo abrir el archivo D1" << endl;
    return 0;
  }

  auto start_const = high_resolution_clock::now();
  while(true){
    uchar* palabra = readWord(filed1);
    if(palabra == nullptr) break; 
    if(length(palabra) > 0) {
        g.insert(palabra);
    }
    delete[] palabra; 
}
  filed1.close();
  g.rebuildGrid(); //parte de la construcción de la estructura

  auto end_const = high_resolution_clock::now();
  duration<double> t_const = end_const - start_const;

  cout << "Tiempo de Construcción inicial D1: " << t_const.count() << " segundos" << endl;

  //medición de inserción y construcción D1
  ifstream filed2(argv[2]);
  if(!filed2.is_open()){
    cout << "No se pudo abrir el archivo D2" << endl;
    return 0;
  }

  //reservar espacio
  uchar* lote_d2[10000];
  int total_d2 = 0;

  while(total_d2 < 10000){
    uchar* palabra = readWord(filed2);
    if(palabra == nullptr) break;
    if(length(palabra) > 0){
      lote_d2[total_d2] = palabra;
      total_d2++;
    } else {
      delete[] palabra;
    }
  }
  filed2.close();

  desordenarPalabras(lote_d2, total_d2);

  //búsqueda masiva
  int encontradas = 0;
  auto start_search = high_resolution_clock::now();
  
  for(int i = 0; i < total_d2; i++){
    if(g.search(lote_d2[i]) != nullptr) {
        encontradas++;
    }
  }
  
  auto end_search = high_resolution_clock::now();
  duration<double> t_search = end_search - start_search;

  cout << "Palabras encontradas exitosamente: " << encontradas << " de " << total_d2 << endl;
  cout << "Tiempo total de busqueda: " << t_search.count() << " segundos." << endl;
  cout << "Tiempo promedio por palabra: " << (t_search.count() / total_d2) << " segundos." << endl;

  //inserción masiva
  int n_insertar = (total_d2 < 5000) ? total_d2 : 5000;
  int inserciones_exitosas = 0;
  
  auto start_insert = high_resolution_clock::now();
  for(int i = 0; i < n_insertar; i++){
    if(g.insert(lote_d2[i])) {        // Intentamos re-insertar en la estructura
        inserciones_exitosas++;
    }
  }

  g.rebuildGrid();
  auto end_insert = high_resolution_clock::now();
  duration<double> t_insert = end_insert - start_insert;

  cout << "Inserciones nuevas realizadas: " << inserciones_exitosas << " de " << n_insertar << " intentadas." << endl;
  cout << "Tiempo total de insercion: " << t_insert.count() << " segundos." << endl;

  //eliminación masiva
  int eliminaciones_exitosas = 0;
  
  auto start_remove = high_resolution_clock::now();
  for(int i = 0; i < n_insertar; i++){
    if(g.remove(lote_d2[i])) {
        eliminaciones_exitosas++;
    }
  }
  
  auto end_remove = high_resolution_clock::now();
  duration<double> t_remove = end_remove - start_remove;

  cout << "Eliminaciones exitosas: " << eliminaciones_exitosas << " de " << n_insertar << " intentadas." << endl;
  cout << "Tiempo total de eliminacion: " << t_remove.count() << " segundos." << endl;

  for(int i = 0; i < total_d2; i++) {  //limpieza final de la memoria dinámica usada para pruebas
      delete[] lote_d2[i];
  }

  return 0;
}


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

