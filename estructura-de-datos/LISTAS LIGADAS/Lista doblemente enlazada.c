#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo *ant;
    struct nodo *sig;
};
typedef struct nodo * NODO;

typedef struct lista{
    NODO inicio;
    NODO final;
}LISTA;

int estaVacia(LISTA *);
void insertarInicio(LISTA *);

int main(){

    return 0;
}

void insertarInicio(LISTA *);
