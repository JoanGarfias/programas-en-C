#include <stdio.h>
#include <stdlib.h>

int main(){
	char aux;
	int cont=0;
	char *texto = (char*) malloc(sizeof(char) * 8);
	
	while((aux=getchar()) != '\n'){
		if(aux=='\b'){
			if(cont>0)
				cont--;
		}
		else{
			cont++;
			if(cont>=8)
				texto = (char * ) realloc((void*)texto, sizeof(char) * cont);
			texto[cont-1] = aux;
		}
	}
	printf("\nPalabra Dinamica: \n%s",texto);
	return 0;
}