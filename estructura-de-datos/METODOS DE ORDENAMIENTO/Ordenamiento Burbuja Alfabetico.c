#include <stdio.h>
#include<time.h>
#define TAM 10

typedef struct alumn{
    char nombre[32];
    float promedio;
}ALUMNO;

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
void imprimir(ALUMNO *);

/*METODO BURBUJA*/
void burbuja(ALUMNO *);

/*METODO QUICKSORT*/
void quicksort(ALUMNO *,int);
void qs(ALUMNO *,int,int);

/*METODO MERGESORT*/
void MergeSort(int, int, int *);
void fusion(int, int, int, int *);

int main(){

	ALUMNO arr[TAM];
    int op,i;

    for(i=0; i<TAM; i++){
        printf("\n\nIngrese el nombre del alumno %i\n--> ", i+1);
        fflush(stdin);
        gets(arr[i].nombre);
        printf("\nIngrese el promediodel alumno %i\n--> ", i+1);
        fflush(stdin);
        scanf("%f", &arr[i].promedio);
    }

    printf("\n\nDesordenado: \n");
    imprimir(arr);

    printf("\n\nOrdenado ascendentemente\n");
    burbuja(arr);
    imprimir(arr);

    printf("\n\nOrdenado descendientemente\n");
    quicksort(arr, TAM);
    imprimir(arr);

	return 0;
}


void imprimir(ALUMNO *arr){
	int i;
	for(i=0; i<TAM; i++){
		printf("%s %f\n",arr[i].nombre, arr[i].promedio);
	}
	printf("\n");
}

void burbuja(ALUMNO *arr){
    int i,j;
    ALUMNO temp;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM-i-1; j++) {
            if (arr[j].promedio < arr[j + 1].promedio) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
	}
	return;
}

void qs(ALUMNO lista[],int limite_izq,int limite_der){
    int izq,der;
    ALUMNO temporal;
    float pivote;
    izq=limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2].promedio;
    do{
        while(lista[izq].promedio<pivote && izq<limite_der)izq++;
        while(pivote<lista[der].promedio && der > limite_izq)der--;
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

void quicksort(ALUMNO lista[],int n){
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
