#include <stdio.h>
#include <stdlib.h>

void leerPromedios(float [], int);
float obtenerPromedio(float [], int);
void listarPromedios(float[], int);

int main(){
	int cant;
	do{
		printf("\nIntroduce el numero de notas a agregar\n--> ");
		scanf("%d", &cant);
		if(cant<=0 || cant>=100){
			system("CLS");
			printf("\nERROR: Numero no valido \n");
			system("PAUSE");
			system("CLS");
		}
	}while(cant<=0 || cant>=100);
	
	float promedios[cant];
	leerPromedios(promedios, cant);
	listarPromedios(promedios, cant);
	printf("\n\nPromedio final: %.1f", obtenerPromedio(promedios, cant));
	return 0;
}

void leerPromedios(float promedios[], int cant){
	int i;
	for(i=0; i<cant; i++){
		do{
			fflush(stdin);
			printf("\nIntroduce la calificacion %i: \n--> ", i+1);
			scanf("%f", &promedios[i]);
			if(promedios[i]<0){
				printf("\nERROR: Introduzca una calificacion valida \n");
				system("CLS");
				system("PAUSE");
			}
		}while(promedios[i]<0);
	}
	return;
}

float obtenerPromedio(float promedios[], int cant){
	int i;
	float prom = 0.0;
	for(i=0; i < cant; i++){
		prom += promedios[i];
	}
	prom /= cant;
	return prom;
}

void listarPromedios(float promedios[], int cant){
	int i;
	for(i=0; i<cant; i++){
		printf("\nCalificacion %i: %.1f", i+1, promedios[i]);
	}
	return;
}