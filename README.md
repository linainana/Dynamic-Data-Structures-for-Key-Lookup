# Dynamic-Data-Structures-for-Key-Lookup
Integrantes: Isidora Llanquimán(aka Hyro404), Francisca Muñoz(aka fm437352), Catalina Provoste(aka linainana), Escarlett Vargas(aka nissydva).

Este proyecto consiste en el diseño, implementación y comparación experimental de tres estructuras de datos dinámicas para la gestión eficiente de diccionarios de palabras: un arreglo dinámico ordenado, una grilla multinivel y un árbol k-ario. Cada estructura permite realizar operaciones de inserción, búsqueda y eliminación de palabras almacenadas en memoria dinámica. El objetivo principal es analizar y comparar el desempeño de las distintas soluciones en términos de tiempo de ejecución y consumo de memoria RAM.

Para la experimentación se utilizan dos archivos de texto:
D1.txt: contiene las palabras utilizadas para construir inicialmente la estructura.
D2.txt: contiene las palabras utilizadas para las pruebas masivas de búsqueda, inserción y eliminación.

Las mediciones realizadas consideran: tiempo de construcción inicial, tiempo total y promedio de búsqueda, tiempo total de inserción, tiempo total de eliminación, consumo de memoria RAM y cantidad de operaciones exitosas.

Para poder acceder al archivo principal:
```bash
# bash
make # Compila de forma automática las tres soluciones

# Para ejecutar las tres soluciones con valores de k preestablecidos;
make run # k=32 para arreglo y grilla, y k=26 fijo para el árbol k-ario

# Para ejecutar las soluciones independientemente con distintos valores de k:
# Para arreglo dinámico (ejemplo k=16):
./arreglo_dinamico ../data/d1.txt ../data/d2.txt 16

# Para grilla multinivel (ejemplo k=16):
./grilla ../data/d1.txt ../data/d2.txt 16

# Para árbol k-ario (trabaja con un alfabeto fijo de 26 letras, por lo que no requiere recibir un valor de k como parámetro)
./kario ../data/d1.txt ../data/d2.txt
