/*
Definir areglo estatico
Dimension del arreglo determinado por el usuario
Calcular la media
Mostrar valores del arreglo

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

float calcProm(int array[]);

int main(){
	int dim,i;
	do{
	printf("\nIntroduce el valor de la dimension del arreglo: \n--> ");
	scanf("%d",&dim);
	}while(dim<=0);
	
	float cals[dim];
	float prom = 0.0;
	
	for(i=0; i<dim; i++){
		printf("\nCal[%i]: ",i+1);
		scanf("%f",&cals[i]);
		prom += cals[i];
	}
	prom /= dim;
	printf("\n\nLa media es: %.2f", prom);
	printf("\n\n");
	for(i=0; i<dim; i++){
		printf("%.2f ",cals[i]);
	}
	return 0;
}

float calcProm(int array[]){
	int i;
	float prom = 0.0;
	for(i=0; i<dim; i++){
		printf("\nCal[%i]: ",i+1);
		scanf("%f",&cals[i]);
		prom += cals[i];
	}
	prom /= (i+1);
	return prom;
}