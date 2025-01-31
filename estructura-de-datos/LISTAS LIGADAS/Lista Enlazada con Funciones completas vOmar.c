#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;


int estaVacia(NODO *);

/*Insertar*/
void insertarInicio(NODO *, int);
void insertarFinal(NODO *, int);
void insertarPosicion(NODO *, int, int);
void insertarOrdenado(NODO *, int);

/*Eliminar*/
void eliminarInicio(NODO *);
int eliminarFinal(NODO *);
void eliminarPosicion(NODO *, int);
int eliminarValor(NODO *, int);

/*Buscar*/
void buscarDato(NODO *, int);

/*Mostrar*/
void mostrar(NODO *);

int main(){

    NODO lista = NULL;

    insertarInicio(&lista, 10);
    mostrar(&lista);
    if(!eliminarFinal(&lista)){
        printf("\nNo se pudo eliminar");
    }
    else{
        printf("\nSe pudo eliminar");
    }
    mostrar(&lista);
    insertarInicio(&lista, 20);
    mostrar(&lista);

    return 0;
}


int estaVacia(NODO *nodo){
    return *nodo == NULL;
}

void insertarInicio(NODO *ini, int dato){
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

void insertarFinal(NODO *ini, int dato){
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

void insertarPosicion(NODO *ini, int pos, int dato){
    NODO aux;
    int i;

    if(pos<0 || estaVacia(ini)){
        printf("\n\nPosicion invalida");
    }
    else{
        aux = *ini;
        for(i=0; i<pos; i++){ //Buscamos la posicion
          aux = aux->sig;
          if(aux == NULL){
            printf("\nPosicion invalida");
            return;
          }
        }
        aux->dato = dato;
    }
}

void eliminarInicio(NODO *ini){
    NODO aux;
    if(estaVacia(ini)){
        printf("\nLa lista ya esta vacia");
        free(aux);
        return;
    }
    else{
        aux = *ini;
        *ini = (*ini)->sig;
        free(aux);

    }
}

int eliminarFinal(NODO *ini){
    NODO aux;
    NODO anterior = NULL;
    if(estaVacia(ini)){
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


void eliminarPosicion(NODO *ini, int pos){
    if(estaVacia(ini) || pos<0){
        printf("\nPosicion no valida o lista vacia");
        return;
    }
    else{
        NODO aux;
        NODO anterior = NULL;
        int i;
        aux = *ini;
        for(i=0; i<pos; i++){
            anterior = aux;
            aux = aux->sig;
            if(aux == NULL){
                printf("\nPosicion no valida");
                return;
            }
        }
        if(anterior==NULL){ //Es el primer elemento
            *ini = aux->sig;
            free(aux);
        }
        else if(aux->sig == NULL){ //Es el ultimo nodo
            anterior->sig = NULL;
            free(aux);
        }
        else{ //Cualquier nodo
            anterior->sig = aux->sig;
            free(aux);
        }

    }
}

void mostrar(NODO *ini){
    if(estaVacia(ini)){
        printf("\nNo se puede mostrar, lista vacia");
        return;
    }
    printf("\n");
    NODO aux = *ini;
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
    printf("\n");
}

void buscarDato(NODO *ini, int dato){
    NODO aux = *ini;
    int i = 0;
    int band = 0;
    int *pos = (int *) calloc(1, sizeof(int));
    if(estaVacia(ini)){
        printf("\nNo se puede realizar una busqueda porque la lista esta vacia");
        return;
    }
    else{
        while(aux!=NULL){
            if(aux->dato == dato){
                pos = (int *) realloc(pos, sizeof(int) * 1 * (band+1) );
                pos[band] = i;
                band += 1;
            }
            aux = aux->sig;
            i++;
        }
    }
    if(band==1){
        printf("\nSe encontro el dato %d en la posicion %d de la lista", dato, *pos);
    }
    else if (band > 1){
        printf("\nSe encontro el dato %d en las posiciones : ", dato);
        for(i=0;i<band; i++)
            printf("%d ", pos[i]);
    }
    else{
        printf("\nNo se encontro el dato %d", dato);
    free(pos);
    }
}

void insertarOrdenado(NODO *ini, int dato){
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
        while(actual != NULL && dato > actual->dato){
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

int eliminarValor(NODO *lista, int dato){
    NODO actual = *lista;
    NODO anterior = NULL;
    NODO aux = NULL;

    if(dato == (*lista)->dato){
        actual = *lista;
        *lista = (*lista)->sig;
        free(actual);
        return 1;
    }
    else{
        anterior = *lista;
        actual = (*lista)->sig;
        while(actual != NULL && actual->dato != dato){
            anterior = actual;
            actual = actual->sig;
        }
        if(actual != NULL){
            aux = actual;
            anterior->sig = actual->sig;
            free(aux);
            return 1;
        }
    }
    return 0;
}
