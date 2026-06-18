#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

typedef unsigned char uchar;

int total_nodos_creados = 0;

struct NodoKario {
    uchar** claves;       
    NodoKario** hijos;    
    int numClaves;        
    bool esHoja;          
    int K;                

    NodoKario(int k, bool hoja) : K(k), esHoja(hoja), numClaves(0) {
        claves = new uchar*[K];
        hijos = new NodoKario*[K + 1];
        for (int i = 0; i < K; i++) claves[i] = nullptr;
        for (int i = 0; i <= K; i++) hijos[i] = nullptr;
        total_nodos_creados++; 
    }

    ~NodoKario() {
        for (int i = 0; i < K; i++) {
            if (claves[i] != nullptr) {
                delete[] claves[i];
            }
        }
        delete[] claves;
        delete[] hijos;
    }
};

//conversión y comparación lexicográfica 
int obtenerLongitud(const string& str) {
    return str.length();
}

uchar* duplicarCadena(const string& str) {
    int len = str.length();
    uchar* destino = new uchar[len + 1];
    for (int i = 0; i < len; i++) destino[i] = (uchar)str[i];
    destino[len] = '\0';
    return destino;
}

int comparar(const uchar* s1, const uchar* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') return 0;
    return (s1[i] == '\0') ? -1 : 1;
}

//limpieza recursiva profunda recorriendo el arreglo completo hasta K
void limpiarArbol(NodoKario* nodo) {
    if (nodo == nullptr) return;
    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->K; i++) { 
            limpiarArbol(nodo->hijos[i]);
        }
    }
    delete nodo;
}

//métodos operacionales del arbol 
bool buscarAux(NodoKario* nodo, const uchar* clave) {
    if (nodo == nullptr) return false;
    int i = 0;
    while (i < nodo->numClaves && comparar(clave, nodo->claves[i]) > 0) {
        i++;
    }
    if (i < nodo->numClaves && comparar(clave, nodo->claves[i]) == 0) {
        return true; 
    }
    if (nodo->esHoja) return false;
    return buscarAux(nodo->hijos[i], clave);
}

void dividirHijo(NodoKario* padre, int i, NodoKario* hijo, int K) {
    //definimos el punto medio exacto de la partición
    int t = (K + 1) / 2; 
    
    //el nuevo nodo (hermano derecho) recibirá la segunda mitad de los elementos
    NodoKario* nuevo = new NodoKario(K, hijo->esHoja);
    
    //calculamos cuántas claves le quedan al nuevo nodo hermano
    nuevo->numClaves = K - t;
    
    //pasar la segunda mitad de las claves al nuevo nodo
    for (int j = 0; j < nuevo->numClaves; j++) {
        nuevo->claves[j] = hijo->claves[j + t];
        hijo->claves[j + t] = nullptr;
    }
    
    //si no es hoja, pasar también la segunda mitad de los hijos correspondientes
    if (!hijo->esHoja) {
        for (int j = 0; j <= nuevo->numClaves; j++) {
            nuevo->hijos[j] = hijo->hijos[j + t];
            hijo->hijos[j + t] = nullptr;
        }
    }
    
    //ajustamos el número de claves que se quedan en el hijo original
    hijo->numClaves = t - 1;

    //hacer espacio en el nodo padre para el nuevo hijo
    for (int j = padre->numClaves; j >= i + 1; j--) {
        padre->hijos[j + 1] = padre->hijos[j];
    }
    padre->hijos[i + 1] = nuevo;

    //hacer espacio en el nodo padre para la clave que sube desde el medio
    for (int j = padre->numClaves - 1; j >= i; j--) {
        padre->claves[j + 1] = padre->claves[j];
    }
    
    //la clave del medio (índice t-1) sube formalmente al padre
    padre->claves[i] = hijo->claves[t - 1];
    hijo->claves[t - 1] = nullptr;
    
    padre->numClaves++;
}

void insertarNoLleno(NodoKario* nodo, const uchar* clave, int K) {
    int i = nodo->numClaves - 1;
    if (nodo->esHoja) {
        while (i >= 0 && comparar(clave, nodo->claves[i]) < 0) {
            nodo->claves[i + 1] = nodo->claves[i];
            i--;
        }
        nodo->claves[i + 1] = duplicarCadena((const char*)clave);
        nodo->numClaves++;
    } else {
        while (i >= 0 && comparar(clave, nodo->claves[i]) < 0) {
            i--;
        }
        i++;
        if (nodo->hijos[i]->numClaves == K) {
            dividirHijo(nodo, i, nodo->hijos[i], K);
            if (comparar(clave, nodo->claves[i]) > 0) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], clave, K);
    }
}

void eliminarAux(NodoKario* nodo, const uchar* clave) {
    if (nodo == nullptr) return;
    
    int i = 0;
    while (i < nodo->numClaves && comparar(clave, nodo->claves[i]) > 0) {
        i++;
    }
    
    //si encontramos la clave en este nodo
    if (i < nodo->numClaves && comparar(clave, nodo->claves[i]) == 0) {
        if (nodo->esHoja) {
            //en las hojas es seguro borrar y desplazar porque no hay hijos abajo
            if (nodo->claves[i] != nullptr) {
                delete[] nodo->claves[i];
            }
            for (int j = i; j < nodo->numClaves - 1; j++) {
                nodo->claves[j] = nodo->claves[j + 1];
            }
            nodo->claves[nodo->numClaves - 1] = nullptr;
            nodo->numClaves--;
        } else {
            //invalidamos la clave sin destruir el puntero del hijo estructural
            if (nodo->claves[i] != nullptr) {
                delete[] nodo->claves[i];
                nodo->claves[i] = duplicarCadena("[eliminado]"); //dejamos una "marca"
            }
        }
    } else {
        //si no está aquí y no es hoja
        if (nodo->esHoja || nodo->hijos[i] == nullptr) return; 
        eliminarAux(nodo->hijos[i], clave);
    }
}

//función de cálculo de memoria dinámica adaptada al tamaño del parámetro K actual
int calcular_memoria_arbol_dinamico(int total_nodos, int K) {
    int mem_por_nodo = (K * sizeof(uchar*)) + ((K + 1) * sizeof(NodoKario*)) + sizeof(int) + sizeof(bool) + sizeof(int);
    int mem = total_nodos * mem_por_nodo;
    mem += sizeof(NodoKario*); //puntero raíz
    return mem;
}

void desordenarPalabras(string arreglo[], int tamano) {
    for (int i = tamano - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arreglo[i], arreglo[j]);
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Modo de uso: ./kario data/d1.txt data/d2.txt <Valor_K>" << endl;
        return 0;
    }

    srand(42); 
    int K_param = atoi(argv[3]);

    NodoKario* raiz = new NodoKario(K_param, true);
    total_nodos_creados = 1;

    //medición de construcción inicial (D1)
    ifstream filed1(argv[1]);
    if (!filed1.is_open()) {
        cout << "No se pudo abrir el archivo D1" << endl;
        delete raiz;
        return 0;
    }

    string palabra;
    auto start_const = high_resolution_clock::now();
    while (filed1 >> palabra) {
        if (!palabra.empty()) {
            uchar* temp_clave = duplicarCadena(palabra);
            if (!buscarAux(raiz, temp_clave)) {
                if (raiz->numClaves == K_param) {
                    NodoKario* nuevaRaiz = new NodoKario(K_param, false);
                    nuevaRaiz->hijos[0] = raiz;
                    dividirHijo(nuevaRaiz, 0, raiz, K_param);
                    raiz = nuevaRaiz;
                }
                insertarNoLleno(raiz, temp_clave, K_param);
            }
            delete[] temp_clave;
        }
    }
    filed1.close();
    auto end_const = high_resolution_clock::now();
    duration<double> t_const = end_const - start_const;

    cout << "Tiempo de construcción inicial D1: " << t_const.count() << " segundos" << endl;
    cout << "Memoria usada: " << calcular_memoria_arbol_dinamico(total_nodos_creados, K_param) << " bytes." << endl;

    //carga y desorden de D2
    ifstream filed2(argv[2]);
    if (!filed2.is_open()) {
        cout << "No se pudo abrir el archivo D2" << endl;
        limpiarArbol(raiz);
        return 0;
    }

    string lote_d2[10000];
    int total_d2 = 0;

    while (total_d2 < 10000 && filed2 >> palabra) {
        if (!palabra.empty()) {
            lote_d2[total_d2] = palabra;
            total_d2++;
        }
    }
    filed2.close();

    desordenarPalabras(lote_d2, total_d2);

    //medición de búsqueda masiva
    int encontradas = 0;
    auto start_search = high_resolution_clock::now();
    
    for (int i = 0; i < total_d2; i++) {
        uchar* temp_busq = duplicarCadena(lote_d2[i]);
        if (buscarAux(raiz, temp_busq)) {
            encontradas++;
        }
        delete[] temp_busq;
    }
    auto end_search = high_resolution_clock::now();
    duration<double> t_search = end_search - start_search;

    cout << "Palabras encontradas exitosamente: " << encontradas << " de " << total_d2 << endl;
    cout << "Tiempo total de búsqueda: " << t_search.count() << " segundos." << endl;
    cout << "Tiempo promedio por palabra: " << (t_search.count() / total_d2) << " segundos." << endl;

    //medición de inserción masiva (5000)
    int n_insertar = (total_d2 < 5000) ? total_d2 : 5000;
    int inserciones_exitosas = 0;
    
    auto start_insert = high_resolution_clock::now();
    for (int i = 0; i < n_insertar; i++) {
        uchar* temp_ins = duplicarCadena(lote_d2[i]);
        if (!buscarAux(raiz, temp_ins)) {
            if (raiz->numClaves == K_param) {
                NodoKario* nuevaRaiz = new NodoKario(K_param, false);
                nuevaRaiz->hijos[0] = raiz;
                dividirHijo(nuevaRaiz, 0, raiz, K_param);
                raiz = nuevaRaiz;
            }
            insertarNoLleno(raiz, temp_ins, K_param);
            inserciones_exitosas++;
        }
        delete[] temp_ins;
    }
    auto end_insert = high_resolution_clock::now();
    duration<double> t_insert = end_insert - start_insert;

    cout << "Inserciones nuevas realizadas: " << inserciones_exitosas << " de " << n_insertar << " intentadas." << endl;
    cout << "Tiempo total de inserción: " << t_insert.count() << " segundos." << endl;

    //medición de eliminación masiva (5000)
    int eliminaciones_exitosas = 0;
    
    auto start_remove = high_resolution_clock::now();
    for (int i = 0; i < n_insertar; i++) {
        uchar* temp_elim = duplicarCadena(lote_d2[i]);
        if (buscarAux(raiz, temp_elim)) {
            eliminarAux(raiz, temp_elim);
            eliminaciones_exitosas++; 
        }
        delete[] temp_elim;
    }
    auto end_remove = high_resolution_clock::now();
    duration<double> t_remove = end_remove - start_remove;

    cout << "Eliminaciones intentadas de forma masiva: " << eliminaciones_exitosas << " de " << n_insertar << endl;
    cout << "Tiempo total de eliminación: " << t_remove.count() << " segundos." << endl;

    //liberación total del árbol al cerrar el programa
    limpiarArbol(raiz);
    return 0;
}
