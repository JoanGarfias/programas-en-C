#include <stdio.h>
#include<stdlib.h>
#include<time.h>
/*
La BUSQUEDA BINARIA es un algoritmo que realiza una busqueda de un dato
las reglas para que funciones son:
    Debe estar ordenado de forma ascendente
    Debe conocerse su tamanio

El algoritmo se va partiendo por la mitad y dependiendo del valor a buscar
se toma un camino (izquierda o derecha)

EJ:
ARREGLO:  1 2 3 4 5
BUSQUEDA: 2

ALGORITMO: mitad=2
-> 1 2 3
ALGORITMO: mitad=1, pos=1
-> 2
Se encontro la busqueda
*/

void MergeSort(int ini, int fin, int *arr);
void fusion(int ini, int mid, int fin, int *arr);
#define TAM 50

int main() {
    int arr[TAM];
    int inf = 0, sup = TAM - 1, mitad = 0, i=0;
    int busqueda;
    char bandera = 'F';
    int pos = -1;

    srand(time(NULL));

    for(i=0; i<TAM; i++)
        arr[i] = rand()% 501;

    for (i = 0; i < TAM; i++) {
        printf("%d ", arr[i]);
    }

    MergeSort(0, TAM-1, arr);

    printf("\n\nIngrese el valor a buscar: \n--> ");
    fflush(stdin);
    scanf("%d", &busqueda);

    while (inf <= sup) {
        mitad = (inf + sup) / 2;
        if (arr[mitad] == busqueda) {
            pos = mitad;
            bandera = 'V';
            break;
        } else {
            if (arr[mitad] > busqueda) {
                sup = mitad - 1;
            } else {
                inf = mitad + 1;
            }
            mitad = (inf + sup) / 2;
        }
    }

    if (pos != -1) {
        printf("\nSe encontro %d en el array %d\n", busqueda, pos);
    } else {
        printf("\nNo se encontro %d en el Array", busqueda);
    }

    return 0;
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
