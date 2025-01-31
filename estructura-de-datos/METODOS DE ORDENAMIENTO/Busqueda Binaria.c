#include <stdio.h>

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

#define TAM 5

int main() {
    int arr[TAM] = {1, 2, 3, 4, 5};
    int inf = 0, sup = TAM - 1, mitad = 0;
    int busqueda = 6;
    char bandera = 'F';

    while (inf <= sup) {
        mitad = (inf + sup) / 2;
        if (arr[mitad] == busqueda) {
            bandera = 'V';
            break;
        } else {
            if (arr[mitad] > busqueda) {
                sup = mitad - 1;
                if (arr[0] > busqueda) {
                    break;
                }
                mitad = (inf + sup) / 2;
            } else {
                inf = mitad + 1;
                if (arr[TAM - 1] < busqueda) {
                    break;
                }
                mitad = (inf + sup) / 2;
            }
        }
    }

    int i;
    for (i = 0; i < TAM; i++) {
        printf("%d ", arr[i]);
    }

    if (bandera == 'V') {
        printf("\nSe encontro %d en el array", busqueda);
    } else {
        printf("\nNo se encontro %d en el Array", busqueda);
    }

    return 0;
}
