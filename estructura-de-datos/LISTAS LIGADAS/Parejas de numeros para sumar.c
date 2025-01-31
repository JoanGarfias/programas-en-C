#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct nodo{
    int dato;
    struct nodo *sig;
    struct nodo *ant;
};
typedef struct nodo * NODO;

void insertarFinal(NODO *, int);
void insertarInicio(NODO *, int);
void insertarOrdenado(NODO *, int);
int eliminarInicio(NODO *);
int eliminarFinal(NODO *);

void verLista(NODO *);

int main(){
    NODO lista = NULL;



    return 0;
}

void insertarOrdenado(NODO *lista, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo)), aux;
    nuevo->dato = dato;
    NODO aux = *lista, anterior = NULL;
    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
        while(aux->sig != NULL && dato > aux->dato){
            anterior = aux;
            aux = aux->sig;
        }

    }
}

void insertarFinal(NODO *lista, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo)), aux;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
        aux = *lista;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
    }

}
void insertarInicio(NODO *lista, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo)), aux;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
        nuevo->sig = *lista;
        *lista = nuevo;
    }
}
int eliminarInicio(NODO *lista){
    int v = -1;
    NODO aux = *lista;
    if(*lista != NULL){
        *lista = (*lista)->sig;
        (*lista)->ant = NULL;
        free(aux);
    }
    return v;
}
int eliminarFinal(NODO *lista){
    int v = -1;
    NODO aux = *lista;
    NODO anterior = NULL;
    if(*lista != NULL){
        while(aux->sig != NULL){
            anterior = aux;
            aux = aux->sig;
        }
        anterior->sig = NULL;
        free(aux);
    }
    return v;
}


void verLista(NODO *lista){
    NODO aux = *lista;
    while(aux!=NULL){
        printf("%d ", aux->dato);
        aux=aux->sig;
    }
    printf("\n\n");
}
