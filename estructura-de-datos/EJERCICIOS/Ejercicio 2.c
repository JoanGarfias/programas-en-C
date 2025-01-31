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

int main(){
	
	float cals = 0.0;
	int cont = 0;
	float aux = -1.0;
	
	while(aux != 0.0){
		cont++;
		printf("\nIntroduce la calificacion %d: ", cont);
		scanf("%f", &aux);
		cals += aux;
		if(aux==0.0){
			printf("\nSaliste \n");
		}
	}
	cont--;
	cals /= cont;
	printf("\nPromedio: %f", cals);
	
	return 0;
}