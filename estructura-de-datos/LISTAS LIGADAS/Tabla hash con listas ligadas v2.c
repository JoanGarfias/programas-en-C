#include<stdio.h>
#include<stdlib.h>

#define MAXTAM 10

struct nodo{
    int dato;
    struct nodo *sig;
};

typedef struct nodo * NODO;

//NODO es un puntero al primer elemento

int funcionHash(int);
void insertar(NODO *, int);
void mostrar(NODO *);

int main(){
    int i;
    NODO *tabla = calloc(MAXTAM, sizeof(NODO));

    for(i=0; i<MAXTAM; i++){
        printf("%p \n", tabla+i);
    }
    printf("\n____________________\n");

    insertar(tabla, 10);
    insertar(tabla, 20);
    insertar(tabla, 30);
    insertar(tabla, 11);
    insertar(tabla, 14);
    insertar(tabla, 34);
    insertar(tabla, 58);


    mostrar(tabla);

    return 0;
}

int funcionHash(int n){
    return n % MAXTAM;
}

void insertar(NODO tabla[], int dato){
    int pos = funcionHash(dato);
    NODO nuevo = (NODO) malloc(sizeof(int));
    NODO *lista = tabla + pos;
    NODO aux = *lista;

    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(nuevo==NULL){
        printf("\nERROR: no hay memoria");
        return;
    }

    if(*lista == NULL){
        *lista = nuevo;
        return;
    }
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    aux->sig = nuevo;
}

void mostrar(NODO *tabla){
    int i;
    NODO aux;
    for(i=0; i<MAXTAM; i++){
        aux = tabla[i];
        while(aux != NULL){
            printf("%d -> ", aux->dato);
            aux = aux->sig;
        }
        printf(" NULL\n");
    }
}
