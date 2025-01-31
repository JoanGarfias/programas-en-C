#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodo{
    float coef;
    int exp;
    struct nodo *sig;
}NODO;

typedef struct lista{
    NODO *ini;
    NODO *fin;
}LISTA;

void insertar(LISTA *, float, int);
int estaVacia(LISTA *);
void mostrar(LISTA *);
void analizarExpresion(LISTA *, char *);

int main(){
    LISTA lista;
    lista.ini = NULL;
    lista.fin = NULL;
    char *expresion = (char *) calloc(32, sizeof(char));

    printf("\n\nIngrese su expresion polinomica\n--> ");
    gets(expresion);
    analizarExpresion(&lista, expresion);

    printf("\n\nExpresion en lista enlazada: \n");
    mostrar(&lista);

    return 0;
}

void analizarExpresion(LISTA *lista, char *expresion){
    char *aux = strtok(expresion, "+-");
    float coef = 1.0;
    int exp = -1;

    while(aux != NULL){
        coef = 1.0;
        exp = -1;

        sscanf(aux, "%fx^%d", &coef, &exp);
        if(exp == -1){
            insertar(lista, coef, 0);
        }
        else{
            insertar(lista, coef, exp);
        }
        aux = strtok(NULL, "+-");
    }
}


int estaVacia(LISTA *lista){
    return lista->ini == NULL;
}

void insertar(LISTA *lista, float coef, int exp){
    NODO *nuevo = (NODO *) malloc(sizeof(struct nodo));
    nuevo->coef = coef;
    nuevo->exp = exp;
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

void mostrar(LISTA *lista){
    NODO *aux = lista->ini;
    while(aux!=NULL){
        printf("%f %d\n", aux->coef, aux->exp);
        aux = aux->sig;
    }
}
