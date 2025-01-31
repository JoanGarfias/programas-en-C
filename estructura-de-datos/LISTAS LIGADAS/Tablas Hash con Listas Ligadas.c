#include<stdio.h>
#include<stdlib.h>

#define MAXTAM 10

typedef struct nodo{
    int dato;
    struct nodo *sig;
}NODO;

typedef struct lista{
    NODO *ini;
    NODO *fin;
}LISTA;

void insertarLista(LISTA *, int);
void eliminarLista(LISTA *, int);
int listaVacia(LISTA *);
void mostrarLista(LISTA *);
int buscarLista(LISTA *, int);

int funcionHash(int);
void insertarTabla(LISTA *, int);
void buscarTabla(LISTA *, int);
void mostrarTabla(LISTA *);

int main(){

    LISTA *tabla = (LISTA *) calloc(MAXTAM, sizeof(LISTA));

    insertarTabla(tabla, 10);
    insertarTabla(tabla, 20);
    insertarTabla(tabla, 30);
    insertarTabla(tabla, 11);
    insertarTabla(tabla, 14);

    mostrarTabla(tabla);

    printf("\n\n-------------------\n");

    buscarTabla(tabla, 1);


    return 0;
}

int funcionHash(int dato){
    return dato % MAXTAM;
}

void insertarTabla(LISTA *tabla, int dato){
    int pos = funcionHash(dato);
    insertarLista(tabla+pos, dato);
}

void buscarTabla(LISTA *tabla, int dato){
    int pos = funcionHash(dato);
    buscarLista(tabla+pos, dato);
}

void mostrarTabla(LISTA *tabla){
    int i;
    for(i=0; i<MAXTAM; i++){
        mostrarLista(tabla+i);
        printf("\n");
    }
}

int listaVacia(LISTA *lista){
    return lista->ini == NULL;
}

void insertarLista(LISTA *lista, int dato){
    NODO *nuevo = (NODO *) malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(nuevo==NULL){
        printf("\nERROR: no hay memoria");
        return;
    }

    if(listaVacia(lista)){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
}

void eliminarLista(LISTA *lista, int dato){
    NODO *aux = lista->ini;
    NODO *ant = NULL;
    NODO *sig = NULL;
    int band = 0;
    while(aux != NULL){
        if(aux->dato == dato){
            if(ant == NULL){  // Verificar si es el primer nodo
                lista->ini = aux->sig;
                if(lista->ini == NULL){  // Si el primer nodo es el único nodo en la lista
                    lista->fin = NULL;
                }
            } else {
                ant->sig = aux->sig;
            }
            free(aux);
            band = 1;
            break;
        }
        ant = aux;
        sig = aux->sig;
        aux = aux->sig;
    }

    if(band)
        printf("\nSe elimino exitosamente el dato %d\n", dato);
    else
        printf("\nNo se encontro %d en la lista\n", dato);
}

void mostrarLista(LISTA *lista){
    if(listaVacia(lista)){
        printf("NULL");
        return;
    }
    NODO *aux = lista->ini;
    while(aux != NULL){
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }
    printf(" NULL");
}

int buscarLista(LISTA *lista, int dato){
    if(listaVacia(lista)){
        printf("\nLa lista esta vacia, no puedo buscar! \n");
        return 0;
    }

    int cont = 0;
    NODO *aux = lista->ini;
    while(aux != NULL){
        if(aux->dato == dato){
            cont++;
        }
        aux = aux->sig;
    }
    printf((cont!=0)? "El dato %d se encontro %d veces" : "No se encontro el dato", dato, cont);
}
