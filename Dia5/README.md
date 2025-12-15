# DIA 5
## ELECCIÓN DEL PROBLEMA
Problema tipico de intervalos donde se puede usar/impleemntar un Arbol de Intervalos para resolverlos, es diferente e interesante.
## ESTRUCTURA DE DATOS UTILIZADA
Arbol de Intervalos
## COMO SE HA ABORDADO EL PROBLEMA
Se ha implementado una Clase para la estructura de datos Arbol de Interavalos y otras dos estructuas que hacen de intervalos y de node del arbol de intervalos, se han agragado todos los intervalos del problema al arbol, luego se han "fusionado". Una vez el arbol contiene los intervalos fusionados para la parte1 del problema se ve si el valor que nos da se encuentra dentro de alguno de los intervalos (se recorre el arbol) y para la parte 2 solamente se calcula la suma de los rangos/longitud interna de cada intervalo.
## ALTERNATIVAS
Uso de un vector de pares<inf, sup> para guardar todos los intervalos y luego ya ver cuales estan en los rangos (recorrer el vector) y la suma interna de los rangos de esos intervalos luego de fusionarlos. 
## QUE SE HA APRENDIDO
La correcta implementacion de un Arbol de Intervalos y la creacion de algunos metodos personalizados para este tipo de problema.
## COMPILAR Y EJECUTAR
Primero: Ir a la pagina web del Advent Of Code, entrar en el apartado de problemas propuestos del año 2025
Segundo: Ir al Problema/Apartado 5 de los problemas que proponen y ver y copiar contenido de "get your puzzle input".
Tercero: Pega el contenido en el archivo de este mismo directorio llamado "input.txt", reemplazando con tu input el contenido actual.
Cuarto: Ya puedes compilar, en una terminal, asegurandote que estas en el directorio con los archivos, haz un "g++ -o nombreaelegir Dia5Alternativo.cpp".
Quinto: Simplemente ejecutalo, se te habra generado un archivo en el directorio llamado igual a "nombreaelegir", simplemente vuelve a escribir en la terminal "./nombreaelegir" y se ejecutara el archivo.
PDD: Las comillas utilizadas son para recalcar y diferenciar la explicacion de las acciones, no tienes que colocarlas.
