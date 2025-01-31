#include <stdio.h>

/*BUSQUEDA SECUENCIAL:
Es la mas facil, solo es buscar un dato
dentro de todo el array
*/

#define TAM 5

int main(){
	
	char estado = 'F';
	int array[TAM] = {1,2,3,2,2};
	int i=0;
	int busqueda = 7;
	
	while(estado=='F' && i<TAM){
		if(array[i] == busqueda){
			estado='V';
		}
		i++;
	}
	
	for(i=0; i<TAM; i++){
		printf("%d ",array[i]);
	}
	
	if(estado=='V'){
		printf("\nSe encontro %d en el array ",busqueda);
	}
	else{
		printf("\nNo se encontro %d en el array", busqueda);
	}
	
}