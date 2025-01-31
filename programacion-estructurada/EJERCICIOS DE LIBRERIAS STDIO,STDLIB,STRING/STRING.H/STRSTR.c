#include <stdio.h>
#include <string.h>

int main() {
   char cadena1[] = "Hola mundo";
   char cadena2[] = "mundo";
   char* resultado = strstr(cadena1, cadena2);
   //STRSTR() busca una cadena en otra
   if(resultado == NULL) {
      printf("'%s' no se encontro en '%s'\n", cadena2, cadena1);
   } else {
      printf("'%s' fue encontrado en '%s' en la posicion %ld\n", cadena2, cadena1, resultado - cadena1);
   }
   
   /*
   
Se hace para obtener la posición en la que se encontró la subcadena cadena2
dentro de la cadena cadena1. En C, los punteros a cadenas de caracteres se pueden
 tratar como si fueran vectores (arrays), por lo que se puede calcular la posición
 de un carácter dentro de una cadena restando los punteros correspondientes.

En este caso, resultado es un puntero al primer carácter de la subcadena cadena2 dentro de cadena1,
 y cadena1 es un puntero al primer carácter de la cadena completa. Por lo tanto, resultado - cadena1
da como resultado la cantidad de caracteres que hay entre cadena1 y resultado, es decir, la posición 
de la subcadena cadena2 dentro de cadena1.
   
   
   */
   
   return 0;
}