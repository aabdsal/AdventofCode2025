# DÍA 11
## ELECCIÓN DEL PROBLEMA
Problema típico de resolución usando grafos. Como para implementar grafos se necesita poder mapear los nodos para acceder a ellos de forma rápida, también se podía implementar una tabla hash.
## ESTRUCTURA DE DATOS UTILIZADA
Grafo dirigido y tabla hash para optimizar y reducir los costes temporales al buscar, recorrer y contar caminos.
## CÓMO SE HA ABORDADO EL PROBLEMA
Se implementó una clase para la estructura de datos "Grafo" y otra para la "HashTable". Se introdujeron todos los nodos del grafo y sus vecinos en la estructura del grafo, creando así las aristas. Estos nodos se mapearon para poder acceder a ellos de forma más eficiente usando la clase/estructura HashTable. Una vez construido el grafo, se utilizó un algoritmo similar al DFS para encontrar todos los caminos que existen desde un nodo a otro.
## ALTERNATIVAS
Probablemente también se hubiese podido resolver con matrices, algún recorrido alternativo a los grafos o incluso con algunos tipos de árboles.
## QUÉ SE HA APRENDIDO
A implementar la clase para usar grafos, a combinar la implementación de tablas hash con grafos para sustituir a "unordered_map", y a implementar funciones para recorrer y contar caminos usando recursividad y programación dinámica.
## COMPILAR Y EJECUTAR
**Para ejecutar con el input proporcionado:**  
Primero: En una terminal, asegúrate de que estás en el directorio que contiene los archivos. Ejecuta
`g++ -std=c++17 -o part1 part1.cpp` y después `./part1` para obtener la solución correspondiente al archivo `input.txt`.

**(Opcional) Para probar con tu propio input y resolver el problema:**  
Primero: Ve a la página web del Advent of Code, accede a los problemas propuestos del año 2025.  
Segundo: Dirígete al problema del día 11 y copia el contenido de "Get your puzzle input".  
Tercero: Pega el contenido en el archivo `input.txt` de este directorio, reemplazando el contenido actual.  
Cuarto: Compila el programa. En la terminal, dentro del directorio de los archivos, ejecuta `g++ -std=c++17 -o <nombre_a_elegir> part1.cpp`.  
Quinto: Ejecuta el programa con `./<nombre_a_elegir>`. Esto te dará la solución para tu input.

**PD:** Las comillas utilizadas en las instrucciones son para recalcar y diferenciar la explicación de las acciones; no es necesario escribirlas.