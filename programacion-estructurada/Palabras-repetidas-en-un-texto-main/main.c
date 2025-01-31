#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TMC 500

void contarPalabras(char []);
void copyStringLim(char [], char *, int, int);
void buscarString(char [], char *, int);
char * vaciarString(char *, int);
void pedirOpcion(int *);

int palabrasRepetidas = 0;

int main(){
	char texto[TMC], buscar[TMC/16];
	int opcion;
	
	printf("\nIntroduzca el texto: \n--->  ");
	fgets(texto, TMC, stdin);
	
	do{
		pedirOpcion(&opcion);
		if(opcion==3) break;
		system("cls");
		printf("\nTexto: \n\n");
		puts(texto);
		switch(opcion){
			case 1: //Buscar todo
				contarPalabras(texto);
				printf("\n\n(!) Hall%c : %d ",130,palabrasRepetidas);
					if(palabrasRepetidas > 1)
						printf("palabras repetidas en total");
					else
						printf("palabra repetida");
				break;
			case 2:
				printf("\nIntroduce la palabra a buscar\n--->  ");
				scanf("%s",buscar);
				buscarString(texto, buscar, 0);
				break;
		}
		printf("\n\n");
		system("PAUSE");
		system("cls");
		fflush(stdin);
	}while(opcion!=3);

	return 0;
}

void pedirOpcion(int *op){
	do{
		system("cls");
		printf("############ MENU DE SELECCION ############");
		printf("\n\t1.- Buscar palabras repetidas");
		printf("\n\t2.- Ingresar palabra y buscar");
		printf("\n\t3.- Salir\n--->  ");
		scanf("%d",op);
	}while(*op<1 || *op>3);
}

void contarPalabras(char texto[TMC]){
	int i=0,j=0;
	int contLetras = 0;
	char * palabra = NULL;
	int sizeCad = (int)strlen(texto)-2;
	for(i=0; i<sizeCad; ){
		while(isalpha(texto[j])){ //contar solo letras
			contLetras++;
			j++;
		}
		palabra = (char *) realloc((void *)palabra, sizeof(char) * (contLetras));
		copyStringLim(texto, palabra, i, j);
		buscarString(texto, palabra, i);
		while(!isalpha(texto[j]) && j<sizeCad){
			j++;
		}
		i=j;
		
		palabra = vaciarString(palabra, contLetras);
		contLetras = 0;
	}
	free(palabra);
}

void copyStringLim(char texto[TMC], char *destino, int pos1, int pos2){
	int i=0,j=0;
	for(i=pos1; i<pos2; i++, j++)
		destino[j] = texto[i];
}

void buscarString(char texto[TMC], char *busqueda, int pos){
	int i=0,j=0, contLetras = 0, Repeticiones = 0, mostrar = 1;
	char * temporal = NULL;
	int sizeCad = (int)strlen(texto)-2;
	for(i=0; i<sizeCad; ){
		while(isalpha(texto[j])){ //se salta el \n
			contLetras++;
			j++;
		}
		temporal = (char *) realloc(temporal, sizeof(char) * (contLetras+1));
		copyStringLim(texto, temporal, i, j);
		if(strcmp(busqueda, temporal) == 0){
			Repeticiones++;
			if(Repeticiones >= 2 && i<=pos){
					mostrar = 0;
					break;
			}
		}
		while(!isalpha(texto[j]) && j<sizeCad){
			j++;
		}
		i=j;
		temporal = vaciarString(temporal, contLetras);
		contLetras = 0;
	}
	if(mostrar && Repeticiones>1){
		printf("\n\nLa palabra %s se repite %d veces\n", busqueda, Repeticiones);
		palabrasRepetidas++;
	}
	free(temporal);
}

char * vaciarString(char *cad, int size){
	int i;
	for(i=0; i<size; i++)
		cad[i] = '\0';
	return cad;
}