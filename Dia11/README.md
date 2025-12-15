# DIA 11
## ELECCIÓN DEL PROBLEMA
Problema tipico de resolucion usando grafos, como para implementar los grafos se necesita poder mapear los nodos para acceder a ellos de forma rapida, tambien se podia implementar una TablaHash
## ESTRUCTURA DE DATOS UTILIZADA
Grafo tipico Dirigido, TablaHash y programacion dinamica para optimizar y bajar costes temporales al buscar, recorrer y contar caminos.
## COMO SE HA ABORDADO EL PROBLEMA
Se ha implementado una Clase para la estructura de datos "Grafos" y otra para la "TablaHash", se han ido introduciendo todos los nodos del grafo y sus vecinos en la estructura del grafo creando asi las aristas, estos nodos se mapeaban para poeder acceder a ellos mas eficientemente usando la clase/estructura TablaHash, una vez el grafo ya esta contruido, se usa un algoritmo parecido al BFS para encontrar todos los caminos que existen desde un nodo a otro, que usa programacion dinamica para optimizar la ejecucion.
## ALTERNATIVAS
Probablemente tambien se hubiese podido resolver con matrices, algun recorrido alternativo a los grafos o incluso con algunos tipos de arboles
## QUE SE HA APRENDIDO
A implementar la clase para usar grafos, a convinar implementacion de TablasHash con Grafos para sustituir a "unordered_map" y a  imlementar funciones de recorrer y contar camninos usando recursividad y programacion dianamica
## COMPILAR Y EJECUTAR
Primero: Ir a la pagina web del Advent Of Code, entrar en el apartado de problemas propuestos del año 2025
Segundo: Ir al Problema/Apartado 11 de los problemas que proponen y ver y copiar contenido de "get your puzzle input".
Tercero: Pega el contenido en el archivo de este mismo directorio llamado "input.txt", reemplazando con tu input el contenido actual.
Cuarto: Ya puedes compilar, en una terminal, asegurandote que estas en el directorio con los archivos, haz un "g++ -o nombreaelegir parte2.cpp.
Quinto: Simplemente ejecutalo, se te habra generado un archivo en el directorio llamado igual a "nombreaelegir", simplemente vuelve a escribir en la terminal "./nombreaelegir" y se ejecutara el archivo dandote la solucion al problema.
PDD: Las comillas utilizadas son para recalcar y diferenciar la explicacion de las acciones, no tienes que colocarlas.
