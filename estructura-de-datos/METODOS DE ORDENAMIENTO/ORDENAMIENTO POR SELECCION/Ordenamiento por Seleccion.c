#include<stdio.h>
#include<windows.h>
/*
El metodo de ordenamiento por seleccion busca el menor de una lista,
guarda su posicion, intercambia su contenido con el numero de la iteración

Ejemplo:

Arreglo:	1 9 2
Posiciones:	0 1 2

Iniciando en i=0
Desde la posicion i=1, se busca hasta i=3
entonces, los numeros a buscar son 9 y 2.

9 < 1? F, no hace nada
2 < 1? F, no hace nada

Iniciando en i=1
ahora va con la posicion i=1, hasta i=3
1 < 2? F, no hace nada
2 < 9? V, intercambia el valor

asi resulta:

1, 2, 9

*/

#define TAM 5

void setColor(WORD col){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),col);
}

int main(){
	
	setColor(4);
	int i,j,aux=0,pos=0;
	int nums[TAM] ={1,9,2,4,11};
	
	for(i=0; i<TAM; i++){
		printf("%d ",nums[i]);
	}
	
	for(i=0; i<TAM; i++){
		pos=i;
		for(j=i+1; j<TAM; j++){
			if(nums[j] < nums[pos]){
				pos = j;
			}
		}
		aux = nums[i];
		nums[i] = nums[pos];
		nums[pos] = aux;
	}
	printf("\nOrdenado: \n");
	setColor(2);
	for(i=0; i<TAM; i++){
		printf("%d ",nums[i]);
	}
	
	
	
}