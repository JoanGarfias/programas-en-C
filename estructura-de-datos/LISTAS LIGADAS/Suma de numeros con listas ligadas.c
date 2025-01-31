#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct nodo{
    int dato;
    struct nodo *sig;
    struct nodo *ant;
};
typedef struct nodo * NODO;

void insertarFinal(NODO *, int);
void insertarInicio(NODO *, int);
int eliminarInicio(NODO *);
int eliminarFinal(NODO *);

void verLista(NODO *);

int main(){
    NODO lista1 = NULL;
    NODO lista2 = NULL;
    char *n1 = calloc(32, sizeof(char));
    char *n2 = calloc(32, sizeof(char));
    int i, t1, t2; //Tamanios


    printf("\nIntroduzca el primer numero");
    fgets(n1, 32, stdin);
    fflush(stdin);
    printf("\nIntroduzca el segundo numero");
    fgets(n2, 32, stdin);
    fflush(stdin);

    for(i=0; n1[i]!='\n'; i++){
        insertarFinal(&lista1, n1[i]-'0');
    }
    for(i=0; n2[i]!='\n'; i++){
        insertarFinal(&lista2, n2[i]-'0');
    }

    NODO aux;
    if(strlen(n2) > strlen(n1)){
        aux = lista2;
        lista2 = lista1;
        lista1 = aux;
    }

    NODO ut1 = lista1;
    while(ut1->sig != NULL){
        ut1 = ut1->sig;
    }
    NODO ut2 = lista2;
    while(ut2->sig != NULL){
        ut2 = ut2->sig;
    }

    NODO suma = NULL;

    int acarreo = 0;
    while(ut2 != NULL){
        if(ut1->dato + ut2->dato >= 10){
            acarreo++;
            insertarInicio(&suma, (ut1->dato + ut2->dato)-10);
        }
        else{
            insertarInicio(&suma, ut1->dato + ut2->dato);
        }
        ut1 = ut1->ant;
        ut2 = ut2->ant;
        if(ut1!=NULL){
            ut1->dato += acarreo;
        }
        if(ut2 == NULL){
            break;
        }
        acarreo=0;
    }
    while(ut1!=NULL){
        insertarInicio(&suma, ut1->dato);
        ut1 = ut1->ant;
    }
    if(acarreo){
        insertarInicio(&suma, acarreo);
    }

    printf("\nLa suma de %s y %s es: \n", n1, n2);
    verLista(&suma);

    return 0;
}

void insertarFinal(NODO *lista, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo)), aux;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
        aux = *lista;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
    }

}
void insertarInicio(NODO *lista, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo)), aux;
    nuevo->dato = dato;

    if(*lista == NULL){
        *lista = nuevo;
    }
    else{
        nuevo->sig = *lista;
        *lista = nuevo;
    }
}
int eliminarInicio(NODO *lista){
    int v = -1;
    NODO aux = *lista;
    if(*lista != NULL){
        *lista = (*lista)->sig;
        (*lista)->ant = NULL;
        free(aux);
    }
    return v;
}
int eliminarFinal(NODO *lista){
    int v = -1;
    NODO aux = *lista;
    NODO anterior = NULL;
    if(*lista != NULL){
        while(aux->sig != NULL){
            anterior = aux;
            aux = aux->sig;
        }
        anterior->sig = NULL;
        free(aux);
    }
    return v;
}


void verLista(NODO *lista){
    NODO aux = *lista;
    while(aux!=NULL){
        printf("%d ", aux->dato);
        aux=aux->sig;
    }
    printf("\n\n");
}
