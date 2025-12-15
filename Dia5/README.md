# DÍA 5
## ELECCIÓN DEL PROBLEMA
Problema típico de intervalos donde se puede usar/implementar un Árbol de Intervalos para resolverlo. Es diferente e interesante.
## ESTRUCTURA DE DATOS UTILIZADA
Árbol de Intervalos.
## CÓMO SE HA ABORDADO EL PROBLEMA
Se ha implementado una clase para la estructura de datos Árbol de Intervalos y otras dos estructuras que representan intervalos y nodos del árbol. Se han agregado todos los intervalos del problema al árbol y luego se han fusionado. Una vez que el árbol contiene los intervalos fusionados, para la parte 1 del problema se comprueba si el valor proporcionado se encuentra dentro de alguno de los intervalos (mediante un recorrido del árbol). Para la parte 2, simplemente se calcula la suma de las longitudes de cada intervalo.
## ALTERNATIVAS
Uso de un vector de pares <inicio, fin> para almacenar todos los intervalos, luego verificar cuáles están dentro de los rangos (recorriendo el vector) y calcular la suma de las longitudes de esos intervalos después de fusionarlos.
## QUÉ SE HA APRENDIDO
La correcta implementación de un Árbol de Intervalos y la creación de algunos métodos personalizados para este tipo de problema.
## COMPILAR Y EJECUTAR
**Para ejecutar con el input proporcionado:**  
Primero: En una terminal, asegúrate de que estás en el directorio que contiene los archivos. Ejecuta `./main` para obtener la solución correspondiente al archivo `input.txt`.

**(Opcional) Para probar con tu propio input y resolver el problema:**  
Primero: Ve a la página web del Advent of Code, accede a los problemas propuestos del año 2025.  
Segundo: Dirígete al problema del día 5 y copia el contenido de "Get your puzzle input".  
Tercero: Pega el contenido en el archivo `input.txt` de este directorio, reemplazando el contenido actual.  
Cuarto: Compila el programa. En la terminal, dentro del directorio de los archivos, ejecuta `g++ -o <nombre_a_elegir> Dia5Alternativo.cpp`.  
Quinto: Ejecuta el programa con `./<nombre_a_elegir>`. Esto te dará la solución para tu input.

**PD:** Las comillas utilizadas en las instrucciones son para recalcar y diferenciar la explicación de las acciones; no es necesario escribirlas.