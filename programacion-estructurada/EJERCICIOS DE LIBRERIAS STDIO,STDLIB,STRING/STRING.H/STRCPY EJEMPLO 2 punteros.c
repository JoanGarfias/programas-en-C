#include <stdio.h>
#include <string.h>
int main(){
	
	char *texto1 = "Hola mundo";
	char texto2[128];
	
	strcpy(texto2, texto1);
	printf("%s\n", texto2);
	
	/*Aqui con aritmetica de apuntadores le dimos la direccion
	 de memoria despues de "hola", lo que hará que se borre mundo
	 y se sobreponga "y bienvenido al lenguaje C"
	*/
	strcpy(texto2+5, "y bienvenido al lenguaje C");
	printf("%s\n",texto2);
	
	return 0;
}