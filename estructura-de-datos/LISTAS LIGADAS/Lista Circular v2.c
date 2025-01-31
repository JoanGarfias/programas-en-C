#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;

int estaVacia(NODO *);
void insertar(NODO *, int);
int eliminarSecuencial(NODO *);

void mostrar(NODO);

int main(){

    NODO lista = NULL;
    int i;
    for(i=10; i<=30; i+=10)
        insertar(&lista, i);

    mostrar(lista);

    printf("\n\n\n");
    eliminarSecuencial(&lista);
    mostrar(lista);

    return 0;
}

int estaVacia(NODO *nodo){
    return *nodo == NULL;
}

void insertar(NODO *ini, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;

    if(estaVacia(ini))
        *ini = nuevo;
    else
        nuevo->sig = (*ini)->sig;

    (*ini)->sig = nuevo;
}

int eliminarSecuencial(NODO *ini){
    int val = -1;
    int i;
    NODO aux = *ini;
    if(*ini == NULL){
        return -1;
    }
    else{
        if(aux == aux->sig){ //Es el unico nodo
            val = aux->dato;
            free(aux);
            *ini = NULL;
        }
        else{
            *ini = (*ini)->sig;
            val = aux->dato;
            free(aux);
        }
    }
    return val;
}

void mostrar(NODO ini){
	NODO aux = ini;
	if(ini!=NULL){
        do{
            printf("%d", aux->dato);
            aux = aux->sig;
            if(aux!=ini){
                printf(" -> ");
            }
        }while(ini != aux);
	}
	else{
        printf("\nLa lista esta vacia");
        return;
	}
}
