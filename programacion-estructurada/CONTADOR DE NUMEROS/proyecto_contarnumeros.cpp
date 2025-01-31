#include<stdio.h>
#include<stdlib.h>
void reducirNumeros(int *,int *, int);
void ordenarNumeros(int *, int);
void contarNumeros(int *, int *, int, int);

int main(){
	int *nums = NULL; //declaramos el apuntador como memoria "nula"
	int *nuevaLista = NULL; //almacenara los numeros reducidos
	int numero, contNums=0;
	do{
		printf("\nIntroduce un numero:\t");
		scanf("%d",&numero);
		contNums++; //le damos uno más al contador de numeros
		if(numero==0) //si mete 0, se sale del ciclo
			break;
		nums = (int *) realloc ((void *)nums,sizeof(int)*contNums); //realojamos memoria segun nos siga dando numeros
		*(nums+(contNums-1)) = numero;
	}while(numero!=0);
	
	
	reducirNumeros(nums,nuevaLista,contNums-1); //le mandamos a la funcion la lista de direcciones de memoria y su contador de numeros
	
	return 0;
}


void reducirNumeros(int *nums, int *nuevaLista, int tam){ //recibe la lista de numeros, una nueva lista, y el tamanio de la lista de numeros
	int i,j,cont=1;	int aux=0;
	printf("tam: %d\n",tam);
	nuevaLista = (int *) realloc ((void *)nuevaLista,sizeof(int)*cont);
	*nuevaLista = *nums;
	for(i=0; i<tam; i++)
		printf("%d ",*(nums+i));
	printf("\n\n\n");
	
	for(i=1; i<tam; i++){
		for(j=0; j < (sizeof(int)*cont)/(sizeof(int) - 1)		; j++){
			if(*(nums+i) == *(nuevaLista+j)) //buscamos si se repite
				aux=1; //si se repite
		}
		if(aux!=1){ //si no se repitio
			cont++;
			nuevaLista = (int *) realloc ((void *)nuevaLista,sizeof(int)*cont);
			*(nuevaLista+cont-1) = *(nums+i);	
		}
		aux=0;
	}
	printf("\n\n");
	for(i=0; i<cont; i++){
		printf("%d ",*(nuevaLista+i));
	}
	printf("\nnueva tamano: %d\n",cont);
	ordenarNumeros(nuevaLista,cont);
	contarNumeros(nuevaLista,nums,cont,tam);
}


void ordenarNumeros(int *nuevaLista, int tam){
	int i,j,aux;
	printf("\n\n");
	for(i=0; i<tam; i++){
		for(j=0; j<tam-1; j++){
			if(nuevaLista[j] > nuevaLista[j+1]){
				aux = nuevaLista[j+1];
				nuevaLista[j+1] = nuevaLista[j];
				nuevaLista[j] = aux;
			}
		}
	}
	for(i=0; i<tam; i++){
		printf("%d ",nuevaLista[i]);
	}
}

void contarNumeros(int *nuevaLista, int *nums, int tam, int tam_nums ){
	int i,j,contNums=0;
	
	for(i=0; i<tam; i++){
		for(j=0; j<tam_nums; j++){
			if(nuevaLista[i] == nums[j]){
				contNums++;
			}
		}
		if(contNums>1)
			printf("\nEl numero %d, me lo diste: %d veces",nuevaLista[i],contNums);
		else
			printf("\nEl numero %d, me lo diste: %d vez",nuevaLista[i],contNums);
	
		contNums=0;
	}
}