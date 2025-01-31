/*Elaborar un programa que genere una matriz bidimensional dinamica de tipo char usando apuntadores, 
buscar la manera de que se pueda imprimir dentro de un procedimiento

se ingresara "!" para indicar el fin del texto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verLista(char **matriz, int tamMatriz){
	int i=0, j=0;
	for(i=0; i<tamMatriz; i++){
		//printf("Tamanio de cadena: %d\n", strlen(matriz[i]));
		for(j=0; j<(int)strlen(matriz[i]); j++)
			printf("%c", matriz[i][j]);
	}
}

int main(){
	int cont = 0, i = 0, contTextos = 0;
	char aux = '\0'; //caracter temporal
	char **textos = (char **) calloc(1, sizeof(char *));
	*textos = (char *) calloc(1, sizeof(char));
	
	do{
		aux = getchar();
		if(aux=='!')
			break;
		cont++;
		textos[contTextos] = (char *) realloc((void *)textos[contTextos], sizeof(char) * (cont + 1));
		
		if(textos[contTextos]==NULL)
			exit(-1);
		
		textos[contTextos][cont-1] = aux;

		if(aux=='\n'){
			textos[contTextos][cont] = '\0';
			textos[contTextos] = &(textos[contTextos][0]);
			contTextos++;
			textos = (char **) realloc(textos, sizeof(char *) * 1 * (contTextos+1));
			
			if(textos==NULL)
				exit(-1);
			cont=0;
		}
	}while(aux!='!');
	
	verLista(textos, contTextos);
	
	for(i=0; i<contTextos; i++)
		free(textos[i]);
	free(textos);
	
	return 0;
}