#include <stdio.h>
#include <string.h>

int main(){ /*strrchr() devuelve una nueva cadena cortada a partir de un 
caracter a buscar

ejemplo:
char nombre[32] = "hola, soy joan"
strrchr(nombre, "j");
devuelve:
	"joan"

strrchr(nombre, "a");
devuelve:
	"an"

BUSCA DE DERECHA A IZQUIERDA

*/
	char texto[64] = "hola soy joan";
	char nuevoTexto[64];
	char busqueda;
	printf("\nIngrese la busqueda\n--> ");
	scanf("%c",&busqueda);
	strcpy(nuevoTexto, strrchr(texto, busqueda));
	printf("%s",nuevoTexto);
	return 0;
}