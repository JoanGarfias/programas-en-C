#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *ant;
    struct nodo *sig;
}* NODO;

NODO ultimoNodo(NODO);
void colarInicio(NODO *, int);
void colarFinal(NODO *, int);
int desencolarInicio(NODO *);
void mostrar(NODO);

int main(){
    int v[] = {1,2,3,4,5,0};
    int i=0;
    NODO cola = NULL;

    while(v[i] != 0){
        colarFinal(&cola, v[i]);
        i++;
    }

    mostrar(cola);
    desencolarInicio(&cola);
    mostrar(cola);

    return 0;
}
NODO ultimoNodo(NODO nodo){
    NODO aux = nodo;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    return aux;
}

void colarInicio(NODO *cola, int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    /*Calloc establece el campo dato en cero, el campo sig en NULL y ant en NULL*/
    nuevo->dato = dato;

    if(*cola == NULL){ //Primer elemento
        *cola = nuevo;
    }
    else{ //Ya hay elementos
        nuevo->sig = *cola; //Establecer conexion entre el nuevo nodo y el inicio de la cola
        (*cola) = nuevo;
    }
}

void colarFinal(NODO *cola, int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    /*Calloc establece el campo dato en cero y el campo sig en NULL*/

    NODO ultimo;

    nuevo->dato = dato;

    if(*cola == NULL){ //Primer elemento
        *cola = nuevo;
    }
    else{ //Ya hay elementos
        ultimo = ultimoNodo(*cola);
        nuevo->ant = ultimo;
        ultimo->sig = nuevo;
    }
}

int desencolarInicio(NODO *cola){
    int v = -1;
    NODO aux = *cola;

    if(*cola == NULL){
        printf("\nCola vacia");
    }
    else{
        v = (*cola)->dato;
        *cola = (*cola)->sig; //Mover el puntero de la cola

        if(*cola != NULL)
            (*cola)->ant = NULL; //Como se vuelve el primero, anterior es NULL
        free(aux);
    }
    return v;
}

int desencolarFinal(NODO *cola){
    int v = -1;
    NODO aux = *cola;
    NODO ultimo;
    NODO penultimo;

    if(*cola == NULL){
        printf("\nCola vacia");
    }
    else{
        if((*cola)->sig == NULL){ //Es el unico nodo
            v = aux->dato;
            free(aux);
            *cola = NULL;
        }
        else{ //Hay mas de un nodo
            ultimo = ultimoNodo(*cola);
            v = aux->dato;
            penultimo = ultimo->ant;
            penultimo->sig = NULL;
            free(aux);
        }
    }
    return v;
}

void mostrar(NODO cola){
    NODO aux = ultimoNodo(cola);
    printf("\n");
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->ant;
    }
}
