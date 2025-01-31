#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo * sig;
};
typedef struct nodo * NODOLISTA;

int estaVacia(NODOLISTA *);

void insertarInicio(NODOLISTA *, int);
void insertarFinal(NODOLISTA *, int);
void insertarPos(NODOLISTA *, int, int);

void eliminarInicio(NODOLISTA *);
void eliminarFinal(NODOLISTA *);

void mostrar(NODOLISTA *);

int main(){

    NODOLISTA lista = NULL;

    insertarInicio(&lista, 1);
    insertarInicio(&lista, 2);
    insertarFinal(&lista, 3);

    mostrar(&lista);

    printf("\n\n");
    eliminarInicio(&lista);

    mostrar(&lista);

    eliminarFinal(&lista);

    printf("\n\n");
    mostrar(&lista);
    //3,1,2
    return 0;
}

int estaVacia(NODOLISTA *nodo){
    return *nodo == NULL;
}

void insertarInicio(NODOLISTA *ini, int dato){
    NODOLISTA aux = (NODOLISTA) malloc(sizeof(struct nodo));
    aux->dato = dato;
    aux->sig = NULL;
    if(estaVacia(ini)){
        *ini = aux;
        return;
    }
    aux->sig = *ini;
    (*ini) = aux;
}

void insertarFinal(NODOLISTA *ini, int dato){
    NODOLISTA nuevo = (NODOLISTA) malloc(sizeof(struct nodo));
    NODOLISTA aux;
    nuevo->dato = dato;
    nuevo->sig = NULL;
    if(estaVacia(ini)){
        nuevo->sig = *ini;
        *ini = nuevo;
    }
    else{
        aux = *ini;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}
/*
void insertarPos(NODO *, int, int){

}*/

void mostrar(NODOLISTA *ini){
    if(estaVacia(ini)){
        printf("\nNo se puede mostrar, la lista esta vacia");
        return;
    }
    NODOLISTA aux = *ini;
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
}

void eliminarInicio(NODOLISTA *ini){
    if(estaVacia(ini)){
        printf("\nLa lista esta vacia");
        return;
    }
    NODOLISTA aux = *ini;
    *ini = aux->sig;
    free(aux);
}

void eliminarFinal(NODOLISTA *ini){
    NODOLISTA aux = *ini;
    if(estaVacia(ini)){
        printf("\nLa lista esta vacia");
    }
    else{
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        free(aux);
    }
}
