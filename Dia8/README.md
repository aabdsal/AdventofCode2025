
# DIA 8
## ELECCIÓN DEL PROBLEMA
Uso de algoritmos/estructuras no utilizadas antes y utiles en algunos casos como sustitutos a grafos completos.
## ESTRUCTURA DE DATOS UTILIZADA
Uso de Divide y Venceras, algotimos de ordenamiento como QuickSort, estructuras de datos lineales como Priority_Queue (forma de Min-Heap) y uso de DSU (Disjoint Set Union) para crear los conjuntos (conexiones) y saber a que conjunto pertenece cada "conexion".
## COMO SE HA ABORDADO EL PROBLEMA
Parte 1: Calculo de todas las distancias euclidianes entre todos los puntos, insercion en una cola de priridad para ordenamiento y mayor velocidad de extraccion, se inluian/unian los puntos en Conjuntos por prioridad ascendente (Min-Heap) luego se incluian los tamaños de cada conjunto en un vector, se ordenava con QuickSort y se calculaba la multiplicacion de los tres mas grandes (primeros tres del vector despues de organizarlo).
Parte 2: Igual que el primero pero no paramos despues de hacer las k-uniones sino que seguimos, siempre que aun queden mas de 1 union por hacer, cuando veamos que solo quedan 2 unione spro hacer, guardamos el ultimo "indice" y el penultimo, apra luego multiplicar sus coordenadas "x".
## ALTERNATIVAS
Usos de Hash Maps personalizados (no resuelve el problema pero si que lo optimiza para algunos implementaciones de resultados del ejercicio) y Grafos haciendo algo parecido a lo mio.
## QUE SE HA APRENDIDO
La forma en la que se implementa un DSU y como puede servir para evitar formar y contruir grafos completos cuando no te interesan ni caminos ni adyacencias ni direcciones.
