PEDRO CROHARÉ. Laboratorio 6 - Algoritmos y estructuras de datos 2 - FaMAF - UNC

INTRODUCCIÓN:
En este proyecto nos centramos en la implementación del algorimto de Dijkstra.
Dicho algoritmo calcula el camino de menor coste entre un vértice fijo y cualquier otro vértice de un mismo grafo direccionado.



COMPILACIÓN:
Antes de compilar, vamos a acceder al directorio "../PEDRO_CROHARE/set object files" y vamos a utilizar el archivo que sea acorde a nuestra arquitectura.
Lo vamos a copiar en el directorio "../PEDRO_CROHARE" y renombrar con el nombre "set.o".

Ahora si, para compilar este pequeño programa, utilizamos las maravillas de la tecnología, siendo el Makefile nuestro amigo.

Abrimos la terminal en el directorio "../PEDRO_CROHARE" y escribimos:
    make            para compilar
    make clean      para eliminar los objetos generados.



EJECUCIÓN: 
Para ejecutar el programa, utilizaremos algunos de los grafos de ejemplo ubicados en el directorio "../PEDRO_CROHARE/input"
El comando a utilizar será el siguiente:

./dijkstra input/example_graph_<ej>.in

Colocando en donde dice <ej> uno de los numeros del 1 al 4, (quitar los caracteres <>)
Para seleccionar alguno de los ejemplos de grafos.



El resultado de compilar y ejecutar el programa con el ejemplo 1 dará este resultado:

Dijkstra Shortest Path Algorithm
Minimum cost from 0 to 0: 0
Minimum cost from 0 to 1: 3
Minimum cost from 0 to 2: 1
Minimum cost from 0 to 3: 8
Minimum cost from 0 to 4: 4
Minimum cost from 0 to 5: 7


Siendo el grafo 1 el siguiente:

0 4 1 10 # #
4 0 3 #  1 #
# 2 0 8  4 #
2 # 2 0  # #
# # 3 #  0 3
# # 2 1  # 0

