# Dynamic-Data-Structures-for-Key-Lookup
Integrantes: Isidora Llanquimán(aka Hyro404), Francisca Muñoz(aka fm437352), Catalina Provoste(aka linainana), Escarlett Vargas(aka nissydva).

Este proyecto es sobre la creación y comparación de estructuras de datos para la gestión de diccionarios, el cual consiste en dos programas (Arreglo Dinámico y Grilla) operados por consola. Se tendrá acceso a cargar grandes cabtidades de palabras desde archivos, buscar palabras específicas y eliminar términos, midiendo los tiempos de ejecución de cada operación con el fin de evaluar y controlar la eficiencia en la búsqueda y almacenamiento de datos.

Indicadores en la interfaz (consola):
Tiempos de construcción y carga: Muestra el tiempo total que tarda la estructura en leer los archivos de texto, alojar las palabras en memoria y construir la estructura (como los niveles de la grilla). Se muestra al inicio del programa con el fin de conocer el costo inicial de preparación de los datos.
Tiempos de búsqueda y eliminación: Muestra el tiempo de CPU (o en segundos) que tarda el programa en encontrar o borrar una palabra específica ingresada por el usuario. Se actualiza cada vez que el usuario realiza una consulta, con el fin de evaluar la velocidad de las estructuras.
Estadísticas de estado: Muestra cuántas palabras se eliminaron de manera exitosa en comparación a las solicitadas, y el número total de palabras restantes dentro de la estructura actual. 
(De esta manera el usuario, conociendo estos datos, puede determinar si el Arreglo Dinámico o la Grilla multinivel es la mejor opción dependiendo de la cantidad del flujo de palabras a procesar.)

Los datos de entrada se leerán desde archivos locales de texto plano con extensión .txt (como d1.txt y d2.txt), los que se cargarán en la memoria dinámica al iniciar el sistema para que las estructuras de datos puedan interactuar con ellos en tiempo real.


Para poder acceder al archivo principal:
```bash
# bash
make # compila de forma automática tanto 'arreglo_dinamico' como 'grilla'

# Para ejecutar el Arreglo Dinámico:
./arreglo_dinamico

# Para ejecutar la Grilla (ejemplo con diccionario d1.txt y k=5):
./grilla d1.txt 5
