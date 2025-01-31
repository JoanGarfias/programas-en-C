#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int contarDigitos(int);
int esCapicuo(int);
int esPar(int);
int esPrimo(int);

int main(){
	int cont=1,i;
	int numero;
	int *numeros = NULL;
	printf("\nSi desea terminar el programa, escriba 0");
	do{
		do{
			printf("\nDame un numero positivo: \t");
			scanf("%d",&numero);
		}while(numero<0);
		if(numero==0)	break;
		numeros = (int *) realloc ((void *)numeros, sizeof(int)*cont);
		*(numeros+cont-1) = numero;
		cont++;
	}while(numero!=0);
	
	for(i=0; i<cont-1; i++){
		printf("\n%d es ",*(numeros+i));
			if(esPar(*(numeros+i)))
				printf("par");
			else
				printf("impar");
			if(esPrimo(*(numeros+i)))
				printf(" primo");
			if(*(numeros+i) > 10){
				if(esCapicuo(*(numeros+i)))
					printf(" capicuo");
			}
	}
	free(numeros);
}

int esPrimo(int numero){
	int i,div=0;
	for(i=2; i<=numero/2; i++){
		if(numero%i==0)
			div++;
	}
	if(div==0 && numero!=1)
		return 1;
	return 0;
}

int esPar(int numero){
	return !(numero%2);
}

int esCapicuo(int num){
	int num_aux=num,i=0;
	int digitos = contarDigitos(num);
	int *numeros_cap = NULL;
	int n1=0,n2=0;
	numeros_cap = (int *) realloc ((void *) numeros_cap, sizeof(int)*digitos);
	for(i=0; i<digitos; i++){
		num_aux = num%10; //guarda el digito de unidad, por ejemplo
		*(numeros_cap+i) = num_aux; //almacenamos cada unidad,centena,etc.
		 num = num/10;
	}
	for(i=0; i<digitos; i++){
		n1 = n1 + *(numeros_cap+i) * pow(10,i);
		n2 = n2 + *(numeros_cap+digitos-i-1) * pow(10,i);
	}
	free(numeros_cap);
	return (n1==n2)?	1 : 0;
}

int contarDigitos(int numero){
	int digitos=0;
	while(numero!=0){
		numero = numero/10;
		digitos++;
	}
	return digitos;
}