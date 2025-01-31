#include<stdio.h>
#include<stdlib.h>
typedef struct pers{
    char nombre[32];
    int edad;
    char sexo;
}PERSONA;

typedef struct nodo{
    PERSONA dato;
    struct nodo *sig;
}NODO;

int estaVacia(NODO **);
void colar(NODO **, PERSONA);
PERSONA desencolar(NODO **);
PERSONA tope(NODO **);
int main(){

    NODO *cola = NULL;
    PERSONA test = {"Joan", 15, 'H'};
    PERSONA asd;
    PERSONA temp;
    colar(&cola, test);
    colar(&cola, (PERSONA) {.nombre="Pablo", .edad=20, .sexo='H'} );
    colar(&cola, (PERSONA) {.nombre="Maraid", .edad=19, .sexo='M'} );

    while(!estaVacia(&cola)){
        temp = desencolar(&cola);
        printf("%s %d %c\n", temp.nombre, temp.edad, temp.sexo);
    }
    //entonces se dice que la cola esta vacia

    return 0;
}

int estaVacia(NODO **ini){
    return *ini == NULL;
}

void colar(NODO **inicio, PERSONA persona){
    if(!estaVacia(inicio)){
        NODO *aux = *inicio;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        NODO *nuevo = (NODO *) malloc(sizeof(NODO));
        nuevo->dato = persona;
        nuevo->sig = NULL;
        aux->sig = nuevo;
    }
    else{
        NODO *nuevo = (NODO *) malloc(sizeof(NODO));
        nuevo->dato = persona;
        nuevo->sig = NULL;
        *inicio = nuevo;
    }
}

PERSONA desencolar(NODO **inicio){
    PERSONA temp;
    if(!estaVacia(inicio)){
        NODO *aux = *inicio;
        temp = aux->dato;
        *inicio = (*inicio)->sig;
        free(aux);
        return temp;
    }
    else{
        printf("\nLa cola ya esta vacia");
    }
}
