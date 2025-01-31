#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *sig;
}NODO;

typedef struct lista{
    NODO *ini;
    NODO *fin;
}LISTA;

void insertar(LISTA *, int);
void eliminar(LISTA *, int);
int estaVacia(LISTA *);
void mostrar(LISTA *);
int buscar(LISTA *, int);

int main(){
    LISTA lista;
    lista.ini = NULL;
    lista.fin = NULL;

    insertar(&lista, 1);
    insertar(&lista, 2);
    insertar(&lista, 3);

    mostrar(&lista);

    eliminar(&lista, 2);
    insertar(&lista, 3);
    mostrar(&lista);
    buscar(&lista, 3);
    return 0;
}

int estaVacia(LISTA *lista){
    return lista->ini == NULL;
}

void insertar(LISTA *lista, int dato){
    NODO *nuevo = (NODO *) malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(nuevo==NULL){
        printf("\nERROR: no hay memoria");
        return;
    }

    if(estaVacia(lista)){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
}

void eliminar(LISTA *lista, int dato){
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

void mostrar(LISTA *lista){
    NODO *aux = lista->ini;
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
    printf("\n\n\n");
}

int buscar(LISTA *lista, int dato){
    if(estaVacia(lista)){
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
