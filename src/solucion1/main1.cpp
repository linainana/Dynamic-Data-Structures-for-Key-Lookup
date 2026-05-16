#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

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

void random(uchar** arreglo, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uchar* tmp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = tmp;
    }
}

int memoria_usada(arreglo_dinamico& arr) {
    //cada puntero ocupa 8 bytes
    int mem = arr.capacidad * 8;

    // cada palabra: largo + 1 bytes
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

int main(){
    srand(42);

    arreglo_dinamico arreglito;
    arreglito.capacidad = 100;
    arreglito.tamano = 0;
    arreglito.overhead = 0.5;
    arreglito.p = new uchar*[arreglito.capacidad];

    for(int i = 0; i < 256; i++){
        arreglito.posiciones[i] = -1;
    }

    string linea;
    clock_t inicio, fin;
    double tiempo_total;

    
    ifstream archivo_d1("D1.txt");

    if (!archivo_d1.is_open()){
        cout << "ERR0R! No se encontró D1.txt" << endl;
    } else{
        cout<< "Cargando..."<< endl;

        inicio = clock();

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
        fin = clock();

        actualizar_posiciones(arreglito);
        

        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;
        cout << "Total palabras: " << arreglito.tamano << endl;
        cout << "Tiempo de insercion: " << tiempo_total << " segundos." << endl;
        cout << "Memoria usada: " << memoria_usada(arreglito) << " bytes." << endl;

    }

    ifstream archivo_d2("D2.txt");

    if(!archivo_d2.is_open()){
        cout << "ERROR! No se encontro D2.txt" << endl;
    }
    uchar* d2_tamano[10000];
    int total_d2 = 0;

    int encontradas = 0;
    while(getline(archivo_d2, linea)){
        limpiar_linea(linea);
        if(linea.empty()) continue;

        int largo = linea.length();

        uchar* palabra_buscar =
            new uchar[largo + 1];

        for(int i = 0; i < largo; i++){
            palabra_buscar[i] =
                (uchar)linea[i];
            }

        palabra_buscar[largo] = '\0';

        d2_tamano[total_d2] = palabra_buscar;
            total_d2++;
    }
    archivo_d2.close();
        
    tiempo_total = (double)(fin - inicio)/CLOCKS_PER_SEC;
    cout << "Encontradas: " << encontradas << endl;
    cout << "Tiempo total busqueda: " << tiempo_total << " seg." << endl;
        

    int n_busquedas;
    if (total_d2 < 10000){
        n_busquedas = total_d2;
    }
    else n_busquedas = 10000;

    cout << "Buscando " << n_busquedas << " palabras de D2..." << endl;

    inicio = clock();
    for (int i = 0; i < n_busquedas; i++) {
        if (busqueda_binaria(arreglito, d2_tamano[i]) != -1) encontradas++;
    }
    fin = clock();

    double tiempo_busqueda = (double)(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Encontradas: " << encontradas << " / " << n_busquedas << endl;
    cout << "Tiempo total busqueda: " << tiempo_busqueda << " seg." << endl;
    cout << "Tiempo promedio por busqueda: " << tiempo_busqueda / n_busquedas << " seg." << endl;

    // ── Insertar primeras 5000 de D2 ───────────
    int n_insertar;
    if (total_d2 < 5000) n_insertar = total_d2;
    else n_insertar = 5000;

    uchar* para_insertar[5000];
    for (int i = 0; i < n_insertar; i++) {
        int largo = 0;
        while (d2_tamano[i][largo] != '\0') largo++;
        uchar* copia = new uchar[largo + 1];
        for (int j = 0; j <= largo; j++) copia[j] = d2_tamano[i][j];
        para_insertar[i] = copia;
    }
    random(para_insertar, n_insertar);

    cout << "\nInsertando " << n_insertar << " palabras de D2 (desordenadas)..." << endl;
    inicio = clock();
    for (int i = 0; i < n_insertar; i++) {
        insertar(arreglito, para_insertar[i]);
    }
    fin = clock();
    actualizar_posiciones(arreglito);

    double tiempo_insercion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Tiempo total insercion D2: " << tiempo_insercion << " seg." << endl;
    cout << "Palabras tras insercion: " << arreglito.tamano << endl;

    //Eliminar ultimas 5000 de D2
    int n_eliminar;
    if (total_d2 < 5000) n_eliminar = total_d2;
    else n_eliminar = 5000;

    int inicio_ultimas = total_d2 - n_eliminar;

    uchar* para_eliminar[5000];
    for (int i = 0; i < n_eliminar; i++) {
        int largo = 0;
        while (d2_tamano[inicio_ultimas + i][largo] != '\0') largo++;
        uchar* copia = new uchar[largo + 1];
        for (int j = 0; j <= largo; j++) copia[j] = d2_tamano[inicio_ultimas + i][j];
        para_eliminar[i] = copia;
    }
    random(para_eliminar, n_eliminar);

    cout << "Eliminando " << n_eliminar << " palabras de D2 (desordenadas)..." << endl;
    int eliminaciones_exitosas = 0;
    inicio = clock();
    for (int i = 0; i < n_eliminar; i++) {
        if (eliminar(arreglito, para_eliminar[i])) eliminaciones_exitosas++;
    }
    fin = clock();

    double tiempo_eliminacion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Eliminaciones exitosas: " << eliminaciones_exitosas << " / " << n_eliminar << endl;
    cout << "Tiempo total eliminacion: " << tiempo_eliminacion << " seg." << endl;
    cout << "Palabras tras eliminacion: " << arreglito.tamano << endl;

    // liberar copias temporales
    for (int i = 0; i < n_eliminar; i++){
        delete[] para_eliminar[i];
    }
    for (int i = 0; i < total_d2; i++) {
        delete[] d2_tamano[i];
    }

    // busqueda usuario
    string palabra_usuario;
    cout << "Escribe una palabra para buscar (o 'salir'): ";

    while (cin >> palabra_usuario && palabra_usuario != "salir") {
        int n = palabra_usuario.length();
        uchar* palabra_buscar = new uchar[n + 1];
        for (int i = 0; i < n; i++){
            palabra_buscar[i] = (uchar)palabra_usuario[i];
        }
        palabra_buscar[n] = '\0';

        clock_t t_ini = clock();
        int r = busqueda_binaria(arreglito, palabra_buscar);
        clock_t t_fin = clock();

        if (r != -1)
            cout << "EXITO! Encontrada en indice: " << r << " -> " << arreglito.p[r] << endl;
        else
            cout << "No existe en el diccionario." << endl;

        cout << "Tiempo CPU: " << (double)(t_fin - t_ini) / CLOCKS_PER_SEC << " seg." << endl;

        delete[] palabra_buscar;
        cout << "Busca otra o escribe 'salir': ";
    }

    for (int i = 0; i < arreglito.tamano; i++){
        delete[] arreglito.p[i];
    }
    delete[] arreglito.p;

    cout << "Memoria liberada. Adios!" << endl;
    return 0;
}
