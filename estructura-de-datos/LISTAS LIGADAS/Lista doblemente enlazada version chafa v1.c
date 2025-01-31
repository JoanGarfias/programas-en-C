#include<stdio.h>
#include<stdlib.h>
struct nodo{
    int dato;
    struct nodo *sig;
    struct nodo *ant;
};
typedef struct nodo * NODO;

void insertarInicio(NODO *, int);
void insertarFinal(NODO *, int);
int eliminarInicio(NODO *);
int eliminarFinal(NODO *);

void mostrar(NODO *);

int main(){

    NODO lista = NULL;
    int i;
    insertarFinal(&lista, 10);
    insertarFinal(&lista, 20);
    insertarFinal(&lista, 30);

    mostrar(&lista);

    return 0;
}

void insertarInicio(NODO *lista, int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->dato = dato;
    if(*lista == NULL){ //Es el primer nodo
        *lista = nuevo;
    }
    else{
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
        *lista = nuevo;
    }
}


void insertarFinal(NODO *lista, int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
        return;
    }

    NODO aux = *lista;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    aux->sig = nuevo;
    nuevo->ant = aux;
}

int eliminarFinal(NODO *lista){
    NODO aux = *lista;
    int v = -1;
    if(*lista != NULL){
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        v = aux->dato;
        NODO ayu = aux;
        aux = aux->ant;
        if (aux != NULL) { //Si la lista no esta vacía
            aux->sig = NULL;
        } else {
            *lista = NULL;
        }
        free(ayu);
    }
    return v;
}

void mostrar(NODO *lista){
    NODO aux = *lista;
    if(aux == NULL){
        printf("NULL");
        return;
    }
    printf("NULL -> ");
    while(aux != NULL){
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }
    printf("NULL\n\n");

    aux = *lista;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    printf("NULL <- ");
    while(aux != NULL){
        printf("%d <- ", aux->dato);
        aux = aux->ant;
    }
    printf("NULL");

    printf("\n\n");
}
