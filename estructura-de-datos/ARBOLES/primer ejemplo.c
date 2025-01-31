#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *izq;
    struct nodo *der;
}* NODO;

void insertar(NODO *, int);
NODO crearNodo(int);
void preOrder(NODO *);
void inOrder(NODO *);
void postOrder(NODO *);

int main(){

    NODO arbol = NULL;

    insertar(&arbol, 20);
    insertar(&arbol, 30);
    insertar(&arbol, 15);
    insertar(&arbol, 22);
    insertar(&arbol, 38);
    insertar(&arbol, 7);
    insertar(&arbol, 19);

    inOrder(&arbol);

    return 0;
}

NODO crearNodo(int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->dato = dato;
}

void insertar(NODO *raiz, int dato){
    if(*raiz == NULL){
        *raiz = crearNodo(dato);
    }
    else{
        if(dato > (*raiz)->dato){
            if((*raiz)->der == NULL){
                (*raiz)->der = crearNodo(dato);
            }
            else{
                insertar(&((*raiz)->der), dato);
            }
        }
        else{
            if((*raiz)->izq == NULL){
                (*raiz)->izq = crearNodo(dato);
            }
            else{
                insertar(&((*raiz)->izq), dato);
            }
        }
    }
}

void preOrder(NODO *arbol){
    if(*arbol != NULL){
        printf("%d ", (*arbol)->dato);
        preOrden(&((*arbol)->izq));
        preOrden(&((*arbol)->der));
    }
}

void inOrder(NODO *arbol){
    if(*arbol != NULL){
        inOrder(&((*arbol)->izq));
        printf("%d ", (*arbol)->dato);
        inOrder(&((*arbol)->der));
    }
}

void postOrder(NODO *arbol){
    if(*arbol != NULL){
        postOrder(&((*arbol)->izq));
        postOrder(&((*arbol)->der));
        printf("%d ", (*arbol)->dato);
    }
}
