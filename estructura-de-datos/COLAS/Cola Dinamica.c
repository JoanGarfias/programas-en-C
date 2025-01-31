#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct nodo{
    char *dato;
    struct nodo *sig;
}NODO;

int estaVacia(NODO **);
void colar(NODO **, char *);
char *desencolar(NODO **);
void limpiar(char *);
char *peek(NODO **);

int main(){
    NODO *cola = NULL;
    char *cancion = (char *) calloc(64, sizeof(char));
    int op;

    do{
        printf("\n1) Agregar cancion");
        printf("\n2) Dejar de escuchar");
        printf("\n3) Escuchando recientemente");
        printf("\n10) Salir\n--> ");
        scanf("%d", &op);
        if(op==10) break;
        system("CLS");
        switch(op){
            case 1:
                limpiar(cancion);
                fflush(stdin);
                printf("\nEscriba el nombre de la cancion: ");
                fgets(cancion, 64, stdin);
                colar(&cola, cancion);
                break;
            case 2:
                printf("\nQuitando %s", desencolar(&cola));
                printf("\nAhora escuchas: %s", peek(&cola));
                break;
            case 3:
                printf("\nEstas escuchando: %s", peek(&cola));
                break;
        }
    }while(op!=10);


    return 0;
}

int estaVacia(NODO **inicio){
    return *inicio == NULL;
}

void colar(NODO **cola, char *cadena){

    char *dato = (char *) calloc(strlen(cadena), sizeof(char) );
    strcpy(dato, cadena);

    if(estaVacia(cola)){
       NODO *nuevo = (NODO *) malloc(sizeof(NODO));
       nuevo->dato = dato;
       nuevo->sig = NULL;
       *cola = nuevo;
    }
    else{
        NODO *aux = *cola;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        NODO *nuevo = (NODO *) malloc(sizeof(NODO));
        nuevo->dato = dato;
        nuevo->sig = NULL;
        aux->sig = nuevo;
    }
}

char *desencolar(NODO **cola){
    if(!estaVacia(cola)){

        char *val = (*cola)->dato;
        NODO *aux = *cola;

        *cola = (*cola)->sig;
        free(aux);

        return val;
    }
    else{
        printf("\nLa cola ya esta vacia");
        return '\0';
    }
}

void limpiar(char *cad){
    int i;
    for(i=0; i<(int)strlen(cad); i++)
        cad[i] = '\0';
}

char *peek(NODO **cola){
    if(!estaVacia(cola)){
        return (*cola)->dato;
    }
    else{
        printf("\nERROR: La cola ya esta vacia");
        return '\0';
    }
}
