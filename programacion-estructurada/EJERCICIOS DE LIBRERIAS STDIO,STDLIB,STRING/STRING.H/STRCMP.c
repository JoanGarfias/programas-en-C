#include <stdio.h>
#include <string.h>
int main(){
	char texto[64] = "Hola soy joan";
	char texto2[64] = "Que onda";
	int value;
	value = strcmp(texto, texto2);
	if(value == 0){
		printf("Las cadenas son iguales");
	}
	else{
		if(value>0){
			printf("\nPrioridad es la segunda %s", texto2);
		}
		else{
			printf("\nPrioridad es la primera %s",texto);
		}
	}
	
	/*Strcmp compara dos cadenas,
	si devuelve un numero negativo, el mayor es el segundo string (alfabetico)
	si devuelve un numero positivo, el mayor es el primer string (alfabetico)
	*/
	
	return 0;
}