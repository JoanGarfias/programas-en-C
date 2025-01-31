#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct nodo{
    char *dato;
    struct nodo *izq;
    struct nodo *der;
}* NODO;

void insertar(NODO *, char *);
NODO crearNodo(char *);
void preOrder(NODO *);
void inOrder(NODO *);
void postOrder(NODO *);
NODO buscarEnArbol(NODO *, char *);

int main(){
    NODO arbol = NULL;
    char *b = (char *) calloc(32, sizeof(char));

    insertar(&arbol, "Nico" );
    insertar(&arbol, "Laura" );
    insertar(&arbol, "Pepe" );
    insertar(&arbol, "Adrian" );
    insertar(&arbol, "Maria" );
    insertar(&arbol, "Tonio" );

    printf("\nPre-Order: \n");
    preOrder(&arbol);
    printf("\nInOrder: \n");
    inOrder(&arbol);
    printf("\nPost-Order: \n");
    postOrder(&arbol);
    printf("\n\n\n");

    printf("\n\nIntroduzca el dato a buscar\n--> ");
    fflush(stdin);
    gets(b);
    NODO busqueda = buscarEnArbol(&arbol, b);

    if(busqueda != NULL){
        printf("\nSe encontro el dato %s y su direccion es %p", busqueda->dato, busqueda);
    }
    else{
        printf("\nNo se encontro el dato");
    }

    return 0;
}

NODO crearNodo(char *dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->dato = dato;
}

void insertar(NODO *raiz, char *dato){
    if(*raiz == NULL){
        *raiz = crearNodo(dato);
    }
    else{
        int r = strcmp(dato, (*raiz)->dato);
        if(r > 0){
            if((*raiz)->der == NULL){
                (*raiz)->der = crearNodo(dato);
            }
            else{
                insertar(&((*raiz)->der), dato);
            }
        }
        else{
            if((*raiz)->izq == NULL){
                (*raiz)->izq = crearNodo(dato);
            }
            else{
                insertar(&((*raiz)->izq), dato);
            }
        }
    }
}

void preOrder(NODO *arbol){
    if(*arbol != NULL){
        printf("%s ", (*arbol)->dato);
        preOrder(&((*arbol)->izq));
        preOrder(&((*arbol)->der));
    }
}

void inOrder(NODO *arbol){
    if(*arbol != NULL){
        inOrder(&((*arbol)->izq));
        printf("%s ", (*arbol)->dato);
        inOrder(&((*arbol)->der));
    }
}

void postOrder(NODO *arbol){
    if(*arbol != NULL){
        postOrder(&((*arbol)->izq));
        postOrder(&((*arbol)->der));
        printf("%s ", (*arbol)->dato);
    }
}

NODO buscarEnArbol(NODO *raiz, char * dato){
    if(*raiz == NULL){
        return NULL;
    }
    else{
        int r = strcmp((*raiz)->dato, dato);
        if(r==0){
            return *raiz;
        }
        else if(r > 0){
            return buscarEnArbol(&((*raiz)->izq), dato);
        }
        else{
            return buscarEnArbol(&((*raiz)->der), dato);
        }
    }
}
