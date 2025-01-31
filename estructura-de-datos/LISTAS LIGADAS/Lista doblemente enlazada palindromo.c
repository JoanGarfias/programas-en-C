#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct nodo{
    char dato;
    struct nodo *sig;
    struct nodo *ant;
};
typedef struct nodo * NODO;

void insertarInicio(NODO *, char);
void insertarFinal(NODO *, char);
char eliminarFinal(NODO *);

void mostrar(NODO *);

int main(){

    NODO lista = NULL;
    int i;
    char *texto = (char *) calloc(32, sizeof(char));
    printf("\n\nIngrese una palabra: \n--> ");
    fgets(texto, 32, stdin);
    for(i=0; texto[i]!='\n'; i++){
        insertarFinal(&lista, texto[i]);
    }
    char aux;
    int palindromo = 1;
    NODO fin = lista;
    NODO ini = lista;

    while(fin->sig != NULL){ //Hallar el ultimo nodo
        fin = fin->sig;
    }

    i=0;

    while(ini != NULL){
        if(ini->dato != fin->dato){
            palindromo = 0;
        }
        ini = ini->sig;
        fin = fin->ant;
    }

    if(palindromo){
        printf("\nEs palindromo");
    }
    else{
        printf("\nNO es palindromo");
    }
    //mostrar(&lista);

    return 0;
}

void insertarInicio(NODO *lista, char dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->dato = dato;
    if(*lista == NULL){ //Es el primer nodo
        *lista = nuevo;
    }
    else{
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
        *lista = nuevo;
    }
}


void insertarFinal(NODO *lista, char dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
        return;
    }

    NODO aux = *lista;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    aux->sig = nuevo;
    nuevo->ant = aux;
}

char eliminarFinal(NODO *lista){
    NODO aux = *lista;
    char v = '\0';
    if(*lista != NULL){
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        v = aux->dato;
        NODO ayu = aux;
        aux = aux->ant;
        if (aux != NULL) { //Si la lista no esta vacía
            aux->sig = NULL;
        } else {
            *lista = NULL;
        }
        free(ayu);
    }
    return v;
}

void mostrar(NODO *lista){
    NODO aux = *lista;
    if(aux == NULL){
        printf("NULL");
        return;
    }
    printf("NULL -> ");
    while(aux != NULL){
        printf("%c -> ", aux->dato);
        aux = aux->sig;
    }
    printf("NULL\n\n");

    aux = *lista;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    printf("NULL <- ");
    while(aux != NULL){
        printf("%c <- ", aux->dato);
        aux = aux->ant;
    }
    printf("NULL");

    printf("\n\n");
}
