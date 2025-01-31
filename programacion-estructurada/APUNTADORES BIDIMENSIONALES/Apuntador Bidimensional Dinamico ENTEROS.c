/*Elaborar un programa que genere una matriz dinamica de tipo enteros usando apuntadores, 
buscar la manera de que se pueda imprimir dentro de un procedimiento, 

se ingresara 0 para indicar el fin de una fila
se ingresara -1 para indicar el fin de la matriz

*/

typedef struct matrices{
	int **mat1;
	int **mat2;
	int **mat3;
	int **mat4;
	int *filas;
	int *columnas;	
	int cont;
}MATRICES;

#include <stdio.h>
#include <stdlib.h>

void agregar(MATRICES *);
void verLista(int **, int, int);

int main(){
	/*Contadores para matriz, contFil quedara fijo, contCol se reinicia cada que se ingresa 0*/
	MATRICES matrices;
	matrices.cont = 0;
	
	agregar(&matrices);
	printf("\n\nMatriz de %d x %d\n\n", matrices.filas[0], matrices.columnas[0]);
	verLista(matrices.mat1, matrices.filas[0], matrices.columnas[0]);
	
	int i = 0;
	
	
	free(matrices.mat1);
	free(matrices.mat2);
	free(matrices.mat3);
	free(matrices.mat4);
	return 0;
}

void verLista(int **matriz, int filas, int columnas){
	int i=0, j=0;
	if(filas==0 || columnas == 0)
		return;
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++)
			printf("%d ", matriz[i][j]);
		printf("\n");
	}
}

void agregar(MATRICES *matrices){
	
	int **matriz = (int **) calloc(1, sizeof(int *));
	*matriz = (int *) calloc(1, sizeof(int));
	int contFil = 0;
	int contCol = 0;
	int aux = 0; /*esta variable almacena un entero temporal de la matriz*/
	do{
		contFil++;
		matriz = (int **) realloc((void*)matriz, sizeof(int *) * (contFil+1) );
		scanf("%d", &aux);
		matriz[contFil] = (int *) calloc(1, sizeof(int));
		if(aux==-1 || aux==0)
			break;
		do{
			fflush(stdin);
			matriz[contFil-1][contCol] = aux;
			matriz[contFil-1] = (int *) realloc(matriz[contFil-1], sizeof(int) * (contCol+1));
			contCol++;
			scanf("%d", &aux);
			if(aux==-1 || aux==0)
				break;
		}while(aux!=0 || aux!=-1);
		if(aux==-1)
			break;
	}while(aux!=-1);
	matrices->cont ++;
	matrices->columnas = (int *) malloc(sizeof(int) * matrices->cont);
	matrices->filas = (int *) malloc(sizeof(int) * matrices->cont);
	matrices->columnas[matrices->cont-1] = contCol;
	matrices->filas[matrices->cont - 1] = contFil;

	switch(matrices->cont){
		case 1:
			matrices->mat1 = matriz;
			//*(matrices->mat1) = *matriz;
			break;
		case 2:
			matrices->mat2 = matriz;
			break;
		case 3:
			matrices->mat3 = matriz;
			break;
		case 4:
			matrices->mat4 = matriz;
			break;
	}
}