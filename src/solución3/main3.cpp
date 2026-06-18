#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

typedef unsigned char uchar;


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
    }


    ~NodoKario() {
        for (int i = 0; i < K; i++) {
            if (claves[i] != nullptr) {
                delete[] claves[i];
                claves[i] = nullptr;
            }
        }
        delete[] claves;
        delete[] hijos;
    }
};


int obtenerLongitud(const uchar* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}


uchar* duplicarCadena(const uchar* origen) {
    int len = obtenerLongitud(origen);
    uchar* destino = new uchar[len + 1];
    for (int i = 0; i < len; i++) destino[i] = origen[i];
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


void limpiarArbol(NodoKario* nodo) {
    if (nodo == nullptr) return;
    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            limpiarArbol(nodo->hijos[i]);
        }
    }
    delete nodo;
}


class ArbolKario {
private:
    NodoKario* raiz;
    int K;


    void dividirHijo(NodoKario* padre, int i, NodoKario* hijo) {
        int t = (K + 1) / 2; 
        NodoKario* nuevo = new NodoKario(K, hijo->esHoja);
        nuevo->numClaves = t - 1;
        for (int j = 0; j < t - 1; j++) {
            nuevo->claves[j] = hijo->claves[j + t];
            hijo->claves[j + t] = nullptr;
        }
        if (!hijo->esHoja) {
            for (int j = 0; j < t; j++) {
                nuevo->hijos[j] = hijo->hijos[j + t];
                hijo->hijos[j + t] = nullptr;
            }
        }


        hijo->numClaves = t - 1;


        for (int j = padre->numClaves; j >= i + 1; j--) {
            padre->hijos[j + 1] = padre->hijos[j];
        }
        padre->hijos[i + 1] = nuevo;


        for (int j = padre->numClaves - 1; j >= i; j--) {
            padre->claves[j + 1] = padre->claves[j];
        }
        padre->claves[i] = hijo->claves[t - 1];
        hijo->claves[t - 1] = nullptr;
        padre->numClaves++;
    }


    void insertarNoLleno(NodoKario* nodo, const uchar* clave) {
        int i = nodo->numClaves - 1;
        if (nodo->esHoja) {
            while (i >= 0 && comparar(clave, nodo->claves[i]) < 0) {
                nodo->claves[i + 1] = nodo->claves[i];
                i--;
            }
            nodo->claves[i + 1] = duplicarCadena(clave);
            nodo->numClaves++;
        } else {
            while (i >= 0 && comparar(clave, nodo->claves[i]) < 0) {
                i--;
            }
            i++;
            if (nodo->hijos[i]->numClaves == K) {
                dividirHijo(nodo, i, nodo->hijos[i]);
                if (comparar(clave, nodo->claves[i]) > 0) {
                    i++;
                }
            }
            insertarNoLleno(nodo->hijos[i], clave);
        }
    }


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


    void eliminarAux(NodoKario* nodo, const uchar* clave) {
        int i = 0;
        while (i < nodo->numClaves && comparar(clave, nodo->claves[i]) > 0) {
            i++;
        }
        if (i < nodo->numClaves && comparar(clave, nodo->claves[i]) == 0) {
            if (nodo->esHoja) {
                delete[] nodo->claves[i];
                for (int j = i; j < nodo->numClaves - 1; j++) {
                    nodo->claves[j] = nodo->claves[j + 1];
                }
                nodo->claves[nodo->numClaves - 1] = nullptr;
                nodo->numClaves--;
            } else {
                NodoKario* predNodo = nodo->hijos[i];
                while (!predNodo->esHoja) {
                    predNodo = predNodo->hijos[predNodo->numClaves];
                }
                uchar* predClaveCopia = duplicarCadena(predNodo->claves[predNodo->numClaves - 1]);
                eliminarAux(nodo->hijos[i], predClaveCopia);
                delete[] nodo->claves[i];
                nodo->claves[i] = predClaveCopia;
            }
        } else {
            if (nodo->esHoja) return; 
            eliminarAux(nodo->hijos[i], clave);
        }
    }


public:
    ArbolKario(int k) : K(k) {
        raiz = new NodoKario(K, true);
    }
    ~ArbolKario() {
        limpiarArbol(raiz);
    }


    void insertar(const uchar* clave) {
        //Evitar inserción de duplicados que rompan la estructura interna
        if (buscar(clave)) return; 
        if (raiz->numClaves == K) {
            NodoKario* nuevaRaiz = new NodoKario(K, false);
            nuevaRaiz->hijos[0] = raiz;
            dividirHijo(nuevaRaiz, 0, raiz);
            raiz = nuevaRaiz;
        }
        insertarNoLleno(raiz, clave);
    }
    bool buscar(const uchar* clave) {
        return buscarAux(raiz, clave);
    }
    void eliminar(const uchar* clave) {
        eliminarAux(raiz, clave);
    }
};


void desordenarArreglo(uchar** arr, int tamano) {
    for (int i = tamano - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uchar* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Uso correcto: ./kario data/d1.txt data/d2.txt <Valor_K>" << endl;
        return 1;
    }
    srand(42); 
    int K_param = atoi(argv[3]);
    cout << "=== INICIANDO EXPERIMENTO CON ÁRBOL K-ARIO (K = " << K_param << ") ===" << endl << endl;
    ArbolKario* arbol = new ArbolKario(K_param);


    //1.Construcción del arbol con D1
    ifstream fileD1(argv[1]);
    if (!fileD1.is_open()) {
        cout << "[ERROR] No se pudo abrir D1: " << argv[1] << endl;
        delete arbol;
        return 1;
    }

    string buffer;
    auto start_const = high_resolution_clock::now();
    while (fileD1 >> buffer) {
        if (!buffer.empty()) {
            arbol->insertar((const uchar*)buffer.c_str());
        }
    }
    fileD1.close();
    auto end_const = high_resolution_clock::now();
    duration<double> t_const = end_const - start_const;
    cout << "1. Tiempo de construccion inicial: " << t_const.count() << " segundos." << endl;


    //2.Obtener total de líneas de D2
    ifstream fileD2(argv[2]);
    if (!fileD2.is_open()) {
        cout << "[ERROR] No se pudo abrir D2: " << argv[2] << endl;
        delete arbol;
        return 1;
    }
    int total_lineas_d2 = 0;
    while (fileD2 >> buffer) { if (!buffer.empty()) total_lineas_d2++; }
    fileD2.close(); // Cerramos y reabrimos para evitar fallos de puntero de archivo en Linux


    //3.Carga de lotes independientes (sin solapamiento)
    uchar* lote_busqueda[10000];
    uchar* lote_insercion[5000];
    uchar* lote_eliminacion[5000];
    int c_busqueda = 0, c_insercion = 0, c_eliminacion = 0;
    int lineas_a_ignorar_elim = total_lineas_d2 - 5000;
    int indice_actual = 0;


    fileD2.open(argv[2]);

    while (fileD2 >> buffer) {
        if (buffer.empty()) continue;
        //Lote de Búsqueda: Primeras 10,000 palabras
        if (indice_actual < 10000) {
            lote_busqueda[c_busqueda++] = duplicarCadena((const uchar*)buffer.c_str());
        }
        //Lote de Inserción: Siguientes 5,000 palabras
        //No se solapa con el de búsqueda para evitar sesgos en la medición.
        if (indice_actual >= 10000 && indice_actual < 15000) {
            lote_insercion[c_insercion++] = duplicarCadena((const uchar*)buffer.c_str());
        }
        //Lote de Eliminación: Últimas 5,000 palabras de D2
        if (indice_actual >= lineas_a_ignorar_elim && c_eliminacion < 5000) {
            lote_eliminacion[c_eliminacion++] = duplicarCadena((const uchar*)buffer.c_str());
        }
        indice_actual++;
    }
    fileD2.close();


    //Mezclar datos de forma independiente
    desordenarArreglo(lote_busqueda, c_busqueda);
    desordenarArreglo(lote_insercion, c_insercion);
    desordenarArreglo(lote_eliminacion, c_eliminacion);


    //Experimentación de búsqueda masiva (10,000 palabras)
    int encontradas = 0;
    auto start_search = high_resolution_clock::now();
    for (int i = 0; i < c_busqueda; i++) {
        if (arbol->buscar(lote_busqueda[i])) {
            encontradas++;
        }
    }
    auto end_search = high_resolution_clock::now();
    duration<double> t_search = end_search - start_search;

    cout << "2. Busqueda Masiva:" << endl;
    cout << "    - Palabras exitosas: " << encontradas << " de " << c_busqueda << " buscadas." << endl;
    cout << "    - Tiempo total: " << t_search.count() << " segundos." << endl;


    //Experimentación de inserción
    auto start_insert = high_resolution_clock::now();
    for (int i = 0; i < c_insercion; i++) {
        arbol->insertar(lote_insercion[i]);
    }
    auto end_insert = high_resolution_clock::now();
    duration<double> t_insert = end_insert - start_insert;

    
    //Experimentación eliminación
    auto start_remove = high_resolution_clock::now();
    for (int i = 0; i < c_eliminacion; i++) {
        arbol->eliminar(lote_eliminacion[i]);
    }
    auto end_remove = high_resolution_clock::now();
    duration<double> t_remove = end_remove - start_remove;

    cout << "3. Inserciones y Eliminaciones Adicionales:" << endl;
    cout << "    - Tiempo total insercion (5000 palabras netas): " << t_insert.count() << " segundos." << endl;
    cout << "    - Tiempo total eliminacion (Ultimas 5000 de D2): " << t_remove.count() << " segundos." << endl;


    //Limpieza final de memoria
    for (int i = 0; i < c_busqueda; i++) delete[] lote_busqueda[i];
    for (int i = 0; i < c_insercion; i++) delete[] lote_insercion[i];
    for (int i = 0; i < c_eliminacion; i++) delete[] lote_eliminacion[i];

    delete arbol;
    return 0;

} 

