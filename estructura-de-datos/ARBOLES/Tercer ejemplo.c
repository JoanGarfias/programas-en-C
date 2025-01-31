#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *izq;
    struct nodo *der;
}* NODO;

void insertar(NODO *, int);
NODO crearNodo(int);
void preOrder(NODO *);
void inOrder(NODO *);
void postOrder(NODO *);
NODO buscarEnArbol(NODO *, int);
NODO eliminarEnArbol(NODO, int);
NODO buscarMenor(NODO);

int main(){

    NODO arbol = NULL;
    int b;

    int arr[] = {120, 140, 87, 43, 99, 130, 135, 22, 63, 93, 56, -1};
    int i;
    for(i=0; arr[i] != -1; i++){
        insertar(&arbol, arr[i]);
    }
    eliminarEnArbol(arbol, 140);

    printf("\nPre-Order: \n");
    preOrder(&arbol);
    printf("\nInOrder: \n");
    inOrder(&arbol);
    printf("\nPost-Order: \n");
    postOrder(&arbol);
    printf("\n\n\n");

    printf("\nIntroduzca el dato a buscar: \n--> ");
    scanf("%d", &b);

    NODO busqueda = buscarEnArbol(&arbol, b);

    if(busqueda != NULL){
        printf("\nSe encontro el dato %d y su direccion es %p", busqueda->dato, busqueda);
        if(busqueda == arbol){
            printf("\nPor cierto, %d es la raiz\n", b);
        }
    }
    else{
        printf("\nNo se encontro el dato %d", b);
    }

    return 0;
}

NODO crearNodo(int dato){
    NODO nuevo = (NODO) calloc(1, sizeof(struct nodo));
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->dato = dato;
}

void insertar(NODO *raiz, int dato){
    if(*raiz == NULL){
        *raiz = crearNodo(dato);
    }
    else{
        if(dato > (*raiz)->dato){
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
        printf("%d ", (*arbol)->dato);
        preOrder(&((*arbol)->izq));
        preOrder(&((*arbol)->der));
    }
}

void inOrder(NODO *arbol){
    if(*arbol != NULL){
        inOrder(&((*arbol)->izq));
        printf("%d ", (*arbol)->dato);
        inOrder(&((*arbol)->der));
    }
}

void postOrder(NODO *arbol){
    if(*arbol != NULL){
        postOrder(&((*arbol)->izq));
        postOrder(&((*arbol)->der));
        printf("%d ", (*arbol)->dato);
    }
}

NODO buscarEnArbol(NODO *raiz, int dato){
    if(*raiz == NULL){
        return NULL;
    }
    else if((*raiz)->dato == dato){
        return *raiz;
    }
    else if(dato > (*raiz)->dato){
        return buscarEnArbol(&((*raiz)->der), dato);
    }
    else{
        return buscarEnArbol(&((*raiz)->izq), dato);
    }
}

NODO eliminarEnArbol(NODO raiz, int dato){
    if(raiz == NULL){
        printf("\nArbol vacio");
        return NULL;
    }
    if(dato < raiz->dato){
        raiz->izq = eliminarEnArbol(raiz->izq, dato);
    }
    if(dato > raiz->dato){
        raiz->der = eliminarEnArbol(raiz->der, dato);
    }
    if(dato == raiz->dato){
        if(raiz->izq == NULL && raiz->der==NULL){ //No tiene hijos (CASO 1)
            free(raiz);
            return NULL;
        }
        if(raiz->izq == NULL){ //Solo tiene hijo a la derecha (CASO 2)
            //Copiar subarbol derecho
            free(raiz);
        }
        if(raiz->der == NULL){ //Solo tiene hijo a la izquierda (CASO 2)
            //Copiar subarbol izquierdo
            free(raiz);
        }
        if(raiz->izq != NULL && raiz->der != NULL){
            NODO menor = buscarMenor(raiz->der);
            raiz->dato = menor->dato;
            eliminarEnArbol(raiz, menor->dato);
            free(menor);
        }
    }

}

NODO buscarMenor(NODO raiz){
    NODO actual = raiz;
    while(actual && actual->izq){
        actual = actual->izq;
    }
    return actual;
}
