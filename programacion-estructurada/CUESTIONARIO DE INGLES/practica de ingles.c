#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct strIngles{
	char espaniol[32];
	char ingles[32];
}LISTA;

int contPalabras = 0;

LISTA * cargarDatos(LISTA *);
void verDatos(LISTA *);
int correcto(LISTA, char *, int);
void vaciarArray(char []);

int main(){
	LISTA *palabras = (LISTA *) malloc(sizeof(LISTA));
	palabras = cargarDatos(palabras);
	//verDatos(palabras);
	char ingresado[32];
	int cont = 0;
	int buenas = 0;
	int malas = 0;
	int validar = 0;
	
	srand(time(NULL));
	int randTraductor = 0;
	int randPalabra = 0;
	char *pal;
	do{
		system("CLS");
		do{
			randPalabra = rand()% contPalabras;
			randTraductor = rand()% 2;
			if(randTraductor == 0)
				pal = palabras[randPalabra].espaniol;
			else
				pal = palabras[randPalabra].ingles;

			printf("\n\nTraduce la palabra %s : ", pal);
			gets(ingresado);
			if((validar = !correcto(*(palabras+randPalabra), ingresado, randTraductor) ) == 1){
				printf("\nNo es la palabra correcta");
			}
			else{
				buenas++;
			}
			if(strcmp(ingresado, "?") == 0){
				malas++;
				validar = 0;
			}
		}while(validar);
		printf("\nCorrecto! la palabra era %s ", palabras[randTraductor].ingles);
		cont++;
	}while(strcmp(ingresado, "!") != 0);
	system("CLS");
	printf("\nTotal de palabras %d", contPalabras);
	printf("\nTotal de Aciertos %d", buenas);
	printf("\nTotal de Malas %d", malas);
	printf("\n\nPromedio: %f", (buenas*100.0)/contPalabras);
	return 0;
}

LISTA * cargarDatos(LISTA *palabras){
	int i;
	FILE *fp = fopen("palabras.txt", "r");
	int lineas = 0;
	while( fscanf(fp , "%s %s", palabras[lineas].espaniol, palabras[lineas].ingles) != EOF) {
		lineas++;
		palabras = (LISTA *) realloc(palabras, sizeof(LISTA) * (lineas+1));
	}
	contPalabras = lineas;
	fclose(fp);
	return palabras;
}

void verDatos(LISTA *palabras){
	int i;
	for(i=0; i<contPalabras; i++){
		printf("%s %s\n", palabras[i].espaniol, palabras[i].ingles);
	}
}

int correcto(LISTA lista, char *ingresado, int idioma){
	if(idioma==0 && strcmp(strupr(lista.ingles), strupr(ingresado) ) == 0){
		return 1;
	}
	else{
		if(idioma==1 && strcmp(strupr(lista.espaniol), strupr(ingresado) ) == 0){
			return 1;
		}
		return 0;
	}
}

void vaciarArray(char arr[]){
	int i;
	for(i=0; i<strlen(arr); i++){
		arr[i] = '\0';
	}
}