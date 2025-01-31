#include <stdio.h>
#include <string.h>

int main(){ /*strchr() devuelve una nueva cadena cortada a partir de un 
caracter a buscar

ejemplo:
char nombre[32] = "hola, soy joan"
strrchr(nombre, "j");
devuelve:
	"joan"

strchr(nombre, "a");
devuelve:
	"a, soy joan"

BUSCA DE IZQUIERDA A DERECHA
devuelve todo lo que hay despues
de encontrar el primer caracter
*/
	char texto[64] = "hola, soy joan";
	char nuevoTexto[64];
	char busqueda;
	printf("\nIngrese la busqueda\n--> ");
	scanf("%c",&busqueda);
	strcpy(nuevoTexto, strchr(texto, busqueda));
	printf("%s",nuevoTexto);
	return 0;
}