#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;

/*Un NODO posee una dirección de memoria, un dato y una dirección de memoria
del siguiente elemento*/

typedef struct lista{
    NODO ini;
    NODO fin;
}LISTA;

LISTA crearLista(); //No es necesario, pero ahorra lineas

int estaVacia(LISTA *);

void insertarInicio(LISTA *, int);
void insertarFinal(LISTA *, int);
void insertar(LISTA *, int);

void eliminarSecuencial(LISTA *);
void eliminarDato(LISTA *, int);
void eliminarLista(LISTA *);

void mostrar(LISTA *);

int main(){
    int i;
    LISTA lista = crearLista();

    for(i=10; i<=90; i+=10){
        insertar(&lista, i);
    }

    mostrar(&lista);

    eliminarDato(&lista, 30);
    eliminarDato(&lista, 10);
    eliminarDato(&lista, 20);
    mostrar(&lista);

    return 0;
}

LISTA crearLista(){
    LISTA temp = {NULL, NULL};
    return temp;
}

int estaVacia(LISTA *lista){
    return lista->ini == NULL;
}

void insertarInicio(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    if(nuevo==NULL)return;

    nuevo->dato = dato;
    nuevo->sig = lista->ini;

    if( !estaVacia(lista) ){
        lista->ini = nuevo;
        lista->fin->sig = nuevo;
    }
    else{
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
}

void insertarFinal(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    if(nuevo==NULL)return;

    nuevo->dato = dato;

    if( !estaVacia(lista) ){ /*Enlazamos el ultimo nodo al final*/
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
    else{ //Si es el primer nodo a insertar
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    nuevo->sig = lista->ini;
}

void mostrar(LISTA *lista){
    if(estaVacia(lista)){
        printf("\nLista vacia");
        return;
    }

    NODO aux = lista->ini;
    do{
        printf("%d ", aux->dato);
        aux = aux->sig;
    }while(aux != lista->ini);
    printf("\n\n\n");
}

void eliminarSecuencial(LISTA *lista){
    if(estaVacia(lista)){
        printf("\nNo se puede eliminar elementos, lista vacia");
        return;
    }

    NODO aux = lista->ini;
    if(aux == aux->sig){ //Es el unico nodo
        free(aux);
        lista->ini = NULL;
        lista->fin = NULL;
    }
    else{ //Hay mas nodos
        lista->ini = aux->sig;
        if(lista->fin->sig != lista->ini){
            lista->fin->sig = lista->ini;
        }
        free(aux);
    }
}

void eliminarDato(LISTA *lista, int dato){
    int exito = 0;
    NODO aux = lista->ini;
    if(aux->sig == lista->ini && aux->dato == dato){
        printf("\nSe elimino el ultimo elemento de la lista %d \n", aux->dato);
        free(aux);
        lista->ini = NULL;
        lista->fin = NULL;
        exito = 1;
        return;
    }

    NODO anterior = lista->ini;
    do{
        if(aux->dato == dato){ //Se encontro el dato
            if(aux == lista->ini){ //Es el primer nodo
                printf("\nEs el primer nodo");
                lista->ini = lista->ini->sig;
                if(lista->fin->sig != lista->ini){ //Validar caso de dos elementos
                    lista->fin->sig = lista->ini;
                }
            }
            else if(aux == lista->fin){ //Es el ultimo nodo
                lista->fin = anterior;
                if(lista->fin->sig != lista->ini){ //Validar caso de dos elementos
                    lista->fin->sig = lista->ini;
                }
            }
            else{ //Cualquier nodo que no sea el inicio o el final
                anterior->sig = aux->sig;
            }
            free(aux);
            exito = 1;
            break;
        }
        anterior = aux;
        aux = aux->sig;
    }while(aux != lista->ini);
    if(exito)
        printf("\nSe elimino el dato %d\n", dato);
    else
        printf("\nNo se encontro el dato %d en la lista\n", dato);
}

void eliminarLista(LISTA *lista){
    NODO actual;
    NODO aux;
    if(!estaVacia(lista)){
        actual = lista->ini;
        if(actual == actual->sig){ //Solo hay un nodo
            free(actual);
            lista->ini = NULL;
            lista->fin = NULL;
        }
        else{
            actual = lista->ini->sig;
            while(actual != lista->ini){
                aux = actual;
                free(aux);
                aux = actual->sig;
            }
            free(lista->ini);
            lista->ini = NULL;
            lista->fin = NULL;
        }
    }
    else{
        printf("\nLa lista esta vacia");
    }
}

void insertar(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;

    if(estaVacia(lista)){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        nuevo->sig = lista->ini->sig;
    }
    lista->ini->sig = nuevo;
    lista->fin = nuevo->sig;
}
