#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct candidato{
    char nombre[32];
    int votos;
}CAND;

struct nodo{
    CAND dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;


int estaVacia(NODO *);

/*Insertar*/
void insertarInicio(NODO *, CAND);
void insertarFinal(NODO *, CAND);

/*Eliminar*/
void eliminarInicio(NODO *);
int eliminarFinal(NODO *);

/*Mostrar*/
void mostrar(NODO *);

void insertarOrdenado(NODO *ini, CAND dato);
void insertarAlfabetico(NODO *ini, CAND dato);

int main(){

    NODO lista = NULL;

    insertarAlfabetico(&lista, (CAND) {"Adrian", 25} );
    insertarAlfabetico(&lista, (CAND) {"Juan", 10} );
    insertarAlfabetico(&lista, (CAND) {"Luis", 30} );
    insertarAlfabetico(&lista, (CAND) {"Caro", 15} );
    insertarAlfabetico(&lista, (CAND) {"Pedro", 25} );
    insertarAlfabetico(&lista, (CAND) {"Bernardo", 26} );

    mostrar(&lista);
    return 0;
}


int estaVacia(NODO *nodo){
    return *nodo == NULL;
}

void insertarInicio(NODO *ini, CAND dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    if(nuevo==NULL)return;

    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(estaVacia(ini)){ //Si esta vacia por defecto agregamos el nodo
       *ini = nuevo;
    }
    else{ //Si no, el siguiente del nuevo es el inicio, y luego el inicio es el nuevo
        nuevo->sig = *ini;
        *ini = nuevo;
    }

}

void insertarFinal(NODO *ini, CAND dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    NODO aux;
    if(nuevo==NULL)return;

    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(estaVacia(ini)){
        *ini = nuevo;
    }
    else{
        aux = *ini;
        while(aux->sig != NULL){ //Buscamos el ultimo nodo
            aux = aux->sig;
        }
        aux->sig = nuevo; //el siguiente del ultimo nodo es el nuevo nodo
    }

}

int eliminarFinal(NODO *ini){
    NODO aux;
    NODO anterior = NULL;
    if(estaVacia(ini)){
        printf("\nLa lista ya esta vacia");
        return 0;
    }
    else{
        aux = *ini;
        while(aux->sig != NULL){
            anterior = aux;
            aux = aux->sig;
        }
        if(anterior == NULL){ //Solo hay un nodo
            *ini = aux->sig;
            free(aux);
        }
        else{
            anterior->sig = NULL;
            free(aux);
        }
    }
    return 1;
}

void mostrar(NODO *ini){
    if(estaVacia(ini)){
        printf("\nLista vacia");
        return;
    }
    printf("\n");
    NODO aux = *ini;
    while(aux != NULL){
        printf("%s %d\n", aux->dato.nombre, aux->dato.votos);
        aux = aux->sig;
    }
    printf("\n");
}

void insertarOrdenado(NODO *ini, CAND dato){
    NODO actual;
    NODO anterior = NULL;
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    if(estaVacia(ini)){
        insertarInicio(ini, dato);
    }
    else{
        actual = *ini;
        while(actual != NULL && dato.votos < actual->dato.votos){
            anterior = actual;
            actual = actual->sig;
        }
        if(anterior == NULL){
            nuevo->sig = *ini;
            *ini = nuevo;
        }
        else{
            nuevo->sig = anterior->sig;
            anterior->sig = nuevo;
        }
    }
}

void insertarAlfabetico(NODO *ini, CAND dato){
    NODO actual;
    NODO anterior = NULL;
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    if(estaVacia(ini)){
        insertarInicio(ini, dato);
    }
    else{
        actual = *ini;
        while(actual != NULL && (strcmp(dato.nombre, actual->dato.nombre) > 0) ){
            anterior = actual;
            actual = actual->sig;
        }
        if(anterior == NULL){
            nuevo->sig = *ini;
            *ini = nuevo;
        }
        else{
            nuevo->sig = anterior->sig;
            anterior->sig = nuevo;
        }
    }
}
