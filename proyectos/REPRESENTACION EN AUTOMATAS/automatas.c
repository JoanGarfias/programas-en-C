#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "automatas.h"

int main(){
	char *rutaAtf = (char *) calloc(64, sizeof(char)); //Nombre del automata (Nombre de la carpeta)
	char *palabra = (char *) calloc(64, sizeof(char));
	int i;

	printf("\nIntroduce el nombre del automata (carpeta) \n--> ");
	gets(rutaAtf);

	AUTOMATA atf = crearAutomata();
	atf = cargarAutomata(rutaAtf);

	imprimirAutomata(atf);

	do{
		printf("\nPara salir no presiones nada y coloca enter \n");
		printf("\n\nIntroduce una cadena para procesarla: \n--> ");
		fgets(palabra, 64, stdin);
		palabra[strlen(palabra)-1] = '\0';
		if(strcmp(palabra, "") == 0) break;
	
		LISTAINT valoresProcesamiento = crearListaInt(0);
		valoresProcesamiento = procesarCadena(atf, palabra, 0, atf.estadoInicial);
		int procesada = valorEnListaInt(valoresProcesamiento, 1);
		printf("\nLa cadena %s ", palabra);	printf((procesada)? " HA SIDO PROCESADA" : " NO PUDO SER PROCESADA");
	}while(1);
	return 0;
}
