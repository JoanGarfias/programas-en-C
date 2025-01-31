#include <stdio.h>
#include <stdlib.h>

void reordenar(int tam, int *arr);
void invertir(int tam, int *arr);
void listar(int tam, int *arr);

int main(){
	int i,tam, *arr;
	do{
		printf("\nIntroduzca el tamanio del arreglo: \n--> ");
		scanf("%d", &tam);
	}while(tam<=0);
	
	arr = (int *) malloc(tam * sizeof(int));
	
	for(i=0; i<tam; i++){
		printf("\nValor [%i]: ", i+1);
		scanf("%d", arr+i);
	}
	listar(tam, arr);
	printf("\n\nInvertido: \n");
	invertir(tam, arr);
	printf("\n\nOrdenado: \n");
	reordenar(tam, arr);
	listar(tam, arr);

	return 0;
}

void invertir(int tam, int *arr){
	int i;
	for(i=tam-1; i>=0; i--){
		printf("%p -> %i \n", arr+i, *(arr+i));
	}
}

void listar(int tam, int *arr){
	int i;
	for(i=0; i<tam; i++)
		printf("%p -> %i\n", arr+i, *(arr+i));
}

void reordenar(int tam, int *nums){
	int i, j, aux=0, pos=0;
	for(i=0; i<tam; i++){
		for(j=0; j<tam-1; j++){
			if(nums[j] > nums[j+1]){
				aux = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = aux;
			}
		}
	}

}