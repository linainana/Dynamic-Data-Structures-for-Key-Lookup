#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

typedef unsigned char uchar;

struct arreglo_dinamico{
    uchar** p;
    int posiciones[256]; 
    int capacidad;
    int tamano;
    double overhead;
};

int comparar(uchar* a, uchar* b){
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0' && a[i] == b[i]){
        i++;
    }
    if(a[i] == b[i]) return 0;
    if(a[i] < b[i])  return -1;
    return 1;
}

//si el tamaño es igual a la capacidad, se debe redimensionar
void redimensionar(arreglo_dinamico& arr){
    int nueva_capacidad = arr.capacidad + (arr.capacidad * arr.overhead);

    if(nueva_capacidad == arr.capacidad){
        nueva_capacidad++;
    }
    uchar** nuevo_p = new uchar*[nueva_capacidad];

    for(int i = 0; i < arr.tamano; i++){
        nuevo_p[i] = arr.p[i];
    }
    delete[] arr.p;

    arr.p = nuevo_p;
    arr.capacidad = nueva_capacidad;

}

void actualizar_posiciones(arreglo_dinamico& arr) {
    for (int i = 0; i < 256; i++){
        arr.posiciones[i] = -1;
    }
    for (int i = 0; i < arr.tamano; i++) {
        uchar primera = arr.p[i][0];
        if (arr.posiciones[primera] == -1)
            arr.posiciones[primera] = i;
    }
}

void insertar(arreglo_dinamico& arr, uchar* nueva_palabra){
    if (arr.tamano == arr.capacidad){
        redimensionar(arr);       
    }
    
    int pos = 0; 

    while(pos < arr.tamano && comparar(arr.p[pos], nueva_palabra) < 0){        
        pos++; 
    } 

    for(int i = arr.tamano; i > pos; i--){
        arr.p[i] = arr.p[i-1];
    } 

    arr.p[pos] = nueva_palabra; 
    arr.tamano++;
}

int busqueda_binaria(arreglo_dinamico& arr, uchar* palabra){
    uchar primera_palabra = palabra[0];
    int izq = arr.posiciones[primera_palabra];
    int der = arr.tamano - 1;

    if (izq == -1){
        return -1;
    }

    for(int i= primera_palabra +1; i < 256; i++){
        if(arr.posiciones[i] != -1){
            der = arr.posiciones[i]-1;
            break;
        }
    }

    while(izq <= der){
        int mitad = izq + (der - izq)/2;

        int comp =
            comparar(arr.p[mitad], palabra);

        if(comp == 0){
            return mitad;
        }

        else if(comp < 0){
            izq = mitad + 1;
        }

        else{
            der = mitad - 1;
        }
    }

    return -1;
}

bool eliminar(arreglo_dinamico& arr , uchar* palabra){
    int pos = busqueda_binaria(arr, palabra);

    if(pos == -1){
        return false;
    }

    delete[] arr.p[pos];

    for(int i = pos; i < arr.tamano - 1; i++){
        arr.p[i] = arr.p[i + 1];
    }
    arr.tamano--;
    actualizar_posiciones(arr);


    return true;
}

void limpiar_linea(string& linea) {
    while (!linea.empty() && (linea.back() == '\r' || linea.back() == '\n' || linea.back() == ' '))
        linea.pop_back();
    while (!linea.empty() && linea.front() == ' ')
        linea.erase(linea.begin());
}

void desordenar_d2(uchar** arreglo, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uchar* tmp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = tmp;
    }
}

int memoria_usada(arreglo_dinamico& arr) {
    int mem = arr.capacidad * 8;

    for (int i = 0; i < arr.tamano; i++) {
        int largo = 0;
        while (arr.p[i][largo] != '\0') largo++;
        mem += largo + 1;
    }

    // el struct usa:
    //uchar** p: 8 bytes, int posiciones[256]: 256 * 4 = 1024 bytes
    //int capacidad: 4 bytes, int tamano: 4 bytes, double overhead: 8 bytes
    mem += 8 + 1024 + 4 + 4 + 8;

    return mem;
}

int main(int argc, char **argv){
    if(argc != 4){
        cout << "Modo de uso: ./arreglo_dinamico ../../data/d1.txt ../../data/d2.txt overhead" << endl;
        return 0;
    }

    cout << fixed;
    cout.precision(10); //muestra los numeros con 10 cifras después del punto decimal
    srand(42);

    arreglo_dinamico arreglito;
    arreglito.capacidad = 100;
    arreglito.tamano = 0;
    arreglito.overhead = atof(argv[3]); 
    arreglito.p = new uchar*[arreglito.capacidad];

    for(int i = 0; i < 256; i++){
        arreglito.posiciones[i] = -1;
    }

    string linea;
    //medicion de construccion D1
    
    ifstream archivo_d1(argv[1]); 

    if (!archivo_d1.is_open()){
        cout << "No se pudo abrir el archivo D1" << endl;
        return 0;
    }
    
    cout << "Cargando archivo d1... " << endl;

    auto start_const = high_resolution_clock::now();

    while(getline(archivo_d1, linea)){
        limpiar_linea(linea);
        if (linea.empty()) continue;

        int largo = linea.length();
        uchar* nueva = new uchar[largo + 1];
        for (int i = 0; i < largo; i++) {
            nueva[i] = (uchar)linea[i];
        }
        nueva[largo] = '\0';

        insertar(arreglito, nueva);
    }
    archivo_d1.close();
    actualizar_posiciones(arreglito);
    
    auto end_const = high_resolution_clock::now();
    duration<double> t_const = end_const - start_const;

    cout << "Total palabras cargadas en D1: " << arreglito.tamano << endl;
    cout << "Tiempo de construccion inicial (D1): " << t_const.count() << " segundos." << endl;
    cout << "Memoria usada: " << memoria_usada(arreglito) << " bytes." << endl;

   
    //cargar d2
    ifstream archivo_d2(argv[2]); 
    if(!archivo_d2.is_open()){
        cout << "No se pudo abrir el archivo D2" << endl;
        return 0;
    }

    uchar* d2_tamano[10000];
    int total_d2 = 0;

    while(getline(archivo_d2, linea) && total_d2 < 10000){
        limpiar_linea(linea);
        if(linea.empty()) continue;

        int largo = linea.length();
        uchar* palabra_buscar = new uchar[largo + 1];
        for(int i = 0; i < largo; i++){
            palabra_buscar[i] = (uchar)linea[i];
        }
        palabra_buscar[largo] = '\0';

        d2_tamano[total_d2] = palabra_buscar;
        total_d2++;
    }
    archivo_d2.close();

    desordenar_d2(d2_tamano, total_d2);

    //búsqueda masiva
    int encontradas = 0;
    cout << "Buscando " << total_d2 << " palabras de d2 desordenadas..." << endl;

    auto start_search = high_resolution_clock::now();
    for (int i = 0; i < total_d2; i++) {
        if (busqueda_binaria(arreglito, d2_tamano[i]) != -1) encontradas++;
    }
    auto end_search = high_resolution_clock::now();
    duration<double> t_search = end_search - start_search;

    cout << "Palabras encontradas exitosamente: " << encontradas << " de " << total_d2 << endl;
    cout << "Tiempo total de busqueda: " << t_search.count() << " segundos." << endl;
    cout << "Tiempo promedio por palabra: " << t_search.count() / total_d2 << " segundos." << endl;

    //inserción masiva
    int n_insertar = (total_d2 < 5000) ? total_d2 : 5000;
    uchar* para_insertar[5000];
    for (int i = 0; i < n_insertar; i++) {
        int largo = 0;
        while (d2_tamano[i][largo] != '\0') largo++;
        uchar* copia = new uchar[largo + 1];
        for (int j = 0; j <= largo; j++) copia[j] = d2_tamano[i][j];
        para_insertar[i] = copia;
    }
    desordenar_d2(para_insertar, n_insertar);

    cout << "Insertando " << n_insertar << " palabras desordenadas..." << endl;
    
    auto start_insert = high_resolution_clock::now();
    for (int i = 0; i < n_insertar; i++) {
        insertar(arreglito, para_insertar[i]);
    }
    actualizar_posiciones(arreglito);
    auto end_insert = high_resolution_clock::now();
    duration<double> t_insert = end_insert - start_insert;

    cout << "Tiempo total de insercion: " << t_insert.count() << " segundos." << endl;
    cout << "Palabras totales tras insercion: " << arreglito.tamano << endl;

    //eliminación masiva
    int n_eliminar = (total_d2 < 5000) ? total_d2 : 5000;
    int inicio_ultimas = total_d2 - n_eliminar;

    uchar* para_eliminar[5000];
    for (int i = 0; i < n_eliminar; i++) {
        int largo = 0;
        while (d2_tamano[inicio_ultimas + i][largo] != '\0') largo++;
        uchar* copia = new uchar[largo + 1];
        for (int j = 0; j <= largo; j++) copia[j] = d2_tamano[inicio_ultimas + i][j];
        para_eliminar[i] = copia;
    }
    desordenar_d2(para_eliminar, n_eliminar);

    cout << "Eliminando " << n_eliminar << " palabras desordenadas..." << endl;
    
    int eliminaciones_exitosas = 0;
    auto start_remove = high_resolution_clock::now();
    for (int i = 0; i < n_eliminar; i++) {
        if (eliminar(arreglito, para_eliminar[i])) eliminaciones_exitosas++;
    }
    auto end_remove = high_resolution_clock::now();
    duration<double> t_remove = end_remove - start_remove;

    cout << "Eliminaciones exitosas: " << eliminaciones_exitosas << " / " << n_eliminar << endl;
    cout << "Tiempo total de eliminacion: " << t_remove.count() << " segundos." << endl;
    cout << "Palabras totales tras eliminacion: " << arreglito.tamano << endl;

    //liberación de memoria
    for (int i = 0; i < n_eliminar; i++) delete[] para_eliminar[i];
    for (int i = 0; i < total_d2; i++) delete[] d2_tamano[i];
    for (int i = 0; i < arreglito.tamano; i++) delete[] arreglito.p[i];
    delete[] arreglito.p;

    cout << "\nMemoria RAM liberada correctamente. ¡Prueba de Arreglo Finalizada!" << endl;
    return 0;
}
