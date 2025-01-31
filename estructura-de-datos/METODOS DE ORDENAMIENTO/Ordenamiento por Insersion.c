#include <stdio.h>

/*El metodo de insercion busca desde un numero
el menor/mayor desde su posicion hasta la posicion cero, si dicho numero
es menor/mayor, las posiciones se van recorriendo hacia la derecha.
*/

#define TAM 5

void impArr(int arr[]);

int main(){
	int i,j;
	int temp;
	int arr[TAM] = {2,7,1,0,13};
	
	impArr(arr);
	
	for(i=1; i<TAM; i++){
		j=i;
		temp = arr[i];
		while(j>0 && (temp < arr[j-1])){
			arr[j] = arr[j-1];
			impArr(arr);
			j--;
		}
		arr[j] = temp;
	}
	printf("\n");
	for(i=0; i<TAM; i++){
		printf("%d ",arr[i]);
	}
	
	return 0;
}

void impArr(int arr[]){
	int i;
	printf("\n");
	for(i=0; i<TAM; i++){
		printf("%d ",arr[i]);
	}
}