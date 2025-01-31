#include <stdio.h>
#include<time.h>
#define TAM 15

/*

El primer ciclo recorre el arreglo n-1 veces, donde n es el número
de elementos en el arreglo. Cada iteración del primer ciclo establece
el número de iteraciones necesarias para que todos los elementos del
arreglo sean comparados y ordenados adecuadamente.

El segundo ciclo se encarga de comparar los elementos adyacentes del arreglo
y hacer los intercambios necesarios si es necesario.

En cada iteración, el segundo ciclo compara un par de elementos adyacentes,
y si el orden es incorrecto, los intercambia.



*/

void generar(int *);
void imprimir(int *);

/*METODO BURBUJA*/
void burbuja(int *);

/*METODO QUICKSORT*/
void quicksort(int *,int);
void qs(int *,int,int);

/*METODO MERGESORT*/
void MergeSort(int, int, int *);
void fusion(int, int, int, int *);
int main(){

	int arr[TAM];
    int op;

    generar(arr);
    printf("\n\nLista desordenada: \n\n");
    imprimir(arr);
    printf("\n\n\n");

    printf("\n\nIngrese el metodo de ordenamiento");
    printf("\n1) Burbuja\n2)QuickSort\n3) MergeSort\n--> ");
    fflush(stdin);
    scanf("%d", &op);

    switch(op){
    case 1:
        burbuja(arr);
        break;
    case 2:
        quicksort(arr, TAM);
        break;
    case 3:
        MergeSort(0,TAM-1, arr);
        break;
    default:
        printf("\n\nMetodo no valido");
        break;
    }

    printf("\n\nOrdenado: \n\n");
    imprimir(arr);
    printf("\n\n");

	return 0;
}

void generar(int *arr){
    srand(time(NULL));
    int i;
    for(i=0; i<TAM; i++){
        arr[i] = rand()% 501;
    }
    printf("\n\nNumeros aleatorios generados automaticamente");
    return;
}

void imprimir(int *arr){
	int i;
	for(i=0; i<TAM; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void burbuja(int *arr){
    int i,j,temp;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM-i-1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
	}
	return;
}

void qs(int lista[],int limite_izq,int limite_der){
    int izq,der,temporal,pivote;
    izq=limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2];
    do{
        while(lista[izq]<pivote && izq<limite_der)izq++;
        while(pivote<lista[der] && der > limite_izq)der--;
        if(izq <=der)
        {
            temporal= lista[izq];
            lista[izq]=lista[der];
            lista[der]=temporal;
            izq++;
            der--;
        }
    }while(izq<=der);
    if(limite_izq<der){qs(lista,limite_izq,der);}
    if(limite_der>izq){qs(lista,izq,limite_der);}
}

void quicksort(int lista[],int n){
    qs(lista,0,n-1);
}

void MergeSort(int ini, int fin, int *arr){
	int mid;
	if(ini < fin){
		mid = (ini+fin) / 2;
		MergeSort(ini,mid, arr);
		MergeSort(mid+1, fin, arr);
		fusion(ini, mid, fin, arr);
	}
}

void fusion(int ini, int mid, int fin, int *arr) {
    int n1 = mid - ini + 1;
    int n2 = fin - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[ini + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = ini;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
