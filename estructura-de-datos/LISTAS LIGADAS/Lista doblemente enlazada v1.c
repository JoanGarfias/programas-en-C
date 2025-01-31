#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo *ant;
    struct nodo *sig;
};
typedef struct nodo * NODO;

typedef struct lista{
    NODO ini;
    NODO fin;
}LISTA;

void insertarInicio(LISTA *,int);
void insertarFinal(LISTA *,int);
int eliminarInicio(LISTA *);
int eliminarFinal(LISTA *);

void mostrar(LISTA *);
void mostrarInverso(LISTA *);

int main(){

    LISTA lista;
    lista.ini = NULL;
    lista.fin = NULL;

    insertarFinal(&lista, 10);
    insertarFinal(&lista, 20);
    insertarFinal(&lista, 30);
    mostrar(&lista);
    eliminarFinal(&lista);
    eliminarFinal(&lista);
    mostrar(&lista);
    mostrarInverso(&lista);
    return 0;
}

void insertarInicio(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->dato = dato;

    if(lista->ini == NULL){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        nuevo->sig = lista->ini;
        lista->ini->ant = nuevo;
        lista->ini = nuevo;
    }

}

void insertarFinal(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->ant = lista->fin;
    nuevo->sig = NULL;
    nuevo->dato = dato;

    if(lista->ini == NULL){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
}

int eliminarInicio(LISTA *lista){
    NODO aux = lista->ini;
    int v = -1;
    if (lista->ini != NULL) {
        v = lista->ini->dato;
        lista->ini = lista->ini->sig;
        if (lista->ini != NULL) { //Si la lista no esta vacía
            lista->ini->ant = NULL;
        } else {
            lista->fin = NULL;
        }
        free(aux);
    }

    return v;
}

int eliminarFinal(LISTA *lista){
    NODO aux = lista->fin;
    int v = -1;
    if(lista->ini != NULL){
        v = lista->fin->dato;
        lista->fin = lista->fin->ant;
       if (lista->fin != NULL) { //Si la lista no esta vacía
            lista->fin->sig = NULL;
        } else {
            lista->ini = NULL;
        }
        free(aux);
    }
    return v;
}

void mostrar(LISTA *lista){
    NODO aux = lista->ini;
    if(aux == NULL){
        printf("\nLista vacia");
        return;
    }

    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
    printf("\n\n\n");
}

void mostrarInverso(LISTA *lista){
    NODO aux = lista->fin;
    if(aux == NULL){
        printf("\nLista vacia");
        return;
    }
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->ant;
    }
    printf("\n\n\n");
}
