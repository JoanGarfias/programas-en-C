#include<stdio.h>
#include<stdlib.h>

struct nodo{
    int dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;

/*Un NODO posee una dirección de memoria, un dato y una dirección de memoria
del siguiente elemento*/

typedef struct lista{
    NODO ini;
    NODO fin;
}LISTA;

LISTA crearLista(); //No es necesario, pero ahorra lineas

int estaVacia(LISTA *);

void insertar(LISTA *, int);
void insertarInicio(LISTA *, int);
void insertarFinal(LISTA *, int);

void eliminarSecuencial(LISTA *);
void eliminarDato(LISTA *, int);
void eliminarLista(LISTA *);

void intercambiar(LISTA *, int, int);

void mostrar(LISTA *);

int main(){
    int i, op, dato, nuevo;
    LISTA lista = crearLista();

    do{
        printf("\n1) Insertar \n2) Insertar al principio");
        printf("\n3) Eliminar siguiente \n4) Eliminar por valor");
        printf("\n5) Borrar lista \n6) Cambiar valor en lista");
        printf("\n7) Mostrar lista \n8) Salir \n--> ");
        fflush(stdin);
        scanf("%d", &op);
        if(op==8)break;
        fflush(stdin);

        switch(op){
        case 1:
            printf("\nIngrese el dato: \n--> ");
            scanf("%d", &dato);
            insertar(&lista, dato);
            break;
        case 2:
            printf("\nIngrese el dato : \n--> ");
            scanf("%d", &dato);
            insertarInicio(&lista, dato);
            break;
        case 3:
            eliminarSecuencial(&lista);
            printf("\nSe ha eliminado el dato");
            break;
        case 4:
            printf("\nIngrese el dato a eliminar: \n--> ");
            scanf("%d", &dato);
            eliminarDato(&lista, dato);
            break;
        case 5:
            eliminarLista(&lista);
            break;
        case 6:
            printf("\nIngrese el dato a cambiar: \n--> ");
            scanf("%d", &dato);
            fflush(stdin);
            printf("\nIngrese el nuevo dato: \n--> ");
            scanf("%d", &nuevo);
            intercambiar(&lista, dato, nuevo);
            break;
        case 7:
            mostrar(&lista);
            break;
        default:
            printf("\nOpcion no valida");
            break;
        }

        printf("\n\n\n");
        system("PAUSE");
        system("CLS");

    }while(op!=8);

    return 0;
}

LISTA crearLista(){
    LISTA temp = {NULL, NULL};
    return temp;
}

int estaVacia(LISTA *lista){
    return lista->ini == NULL;
}

void insertarInicio(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    if(nuevo==NULL)return;

    nuevo->dato = dato;

    if( !estaVacia(lista) ){
        nuevo->sig = lista->ini;
        lista->ini = nuevo;
        lista->fin->sig = nuevo;
    }
    else{
        nuevo->sig = nuevo;
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
}

void insertarFinal(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    if(nuevo==NULL)return;

    nuevo->dato = dato;

    if( !estaVacia(lista) ){ /*Enlazamos el ultimo nodo al final*/
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
    else{ //Si es el primer nodo a insertar
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    nuevo->sig = lista->ini;
}

void mostrar(LISTA *lista){
    if(estaVacia(lista)){
        printf("\nLista vacia");
        return;
    }
    NODO aux = lista->ini;
    if(aux == aux->sig){
        printf("%d ", aux->dato);
        return;
    }
    do{
        printf("%d ", aux->dato);
        aux = aux->sig;
    }while(aux != lista->ini);
    printf("\n\n\n");
}

void eliminarSecuencial(LISTA *lista){
    if(estaVacia(lista)){
        printf("\nNo se puede eliminar elementos, lista vacia");
        return;
    }

    NODO aux = lista->ini;
    if(aux == aux->sig){ //Es el unico nodo
        free(aux);
        lista->ini = NULL;
        lista->fin = NULL;
    }
    else{ //Hay mas nodos
        lista->ini = aux->sig;
        if(lista->fin->sig != lista->ini)
            lista->fin->sig = lista->ini;
        else
            lista->fin->sig = lista->ini;
        free(aux);
    }
}

void eliminarDato(LISTA *lista, int dato){
    int exito = 0;
    NODO aux = lista->ini;
    if(aux->sig == lista->ini && aux->dato == dato){
        printf("\nSe elimino el ultimo elemento de la lista %d \n", aux->dato);
        free(aux);
        lista->ini = NULL;
        lista->fin = NULL;
        exito = 1;
        return;
    }

    NODO anterior = lista->ini;
    do{
        if(aux->dato == dato){ //Se encontro el dato
            if(aux == lista->ini){ //Es el primer nodo
                lista->ini = lista->ini->sig;
                if(lista->fin->sig != lista->ini){ //Validar caso de dos elementos
                    lista->fin->sig = lista->ini;
                }
            }
            else if(aux == lista->fin){ //Es el ultimo nodo
                lista->fin = anterior;
                if(lista->fin->sig != lista->ini){ //Validar caso de dos elementos
                    lista->fin->sig = lista->ini;
                }
            }
            else{ //Cualquier nodo que no sea el inicio o el final
                anterior->sig = aux->sig;
            }
            free(aux);
            exito = 1;
            break;
        }
        anterior = aux;
        aux = aux->sig;
    }while(aux != lista->ini);
    if(exito)
        printf("\nSe elimino el dato %d\n", dato);
    else
        printf("\nNo se encontro el dato %d en la lista\n", dato);
}

void eliminarLista(LISTA *lista){
    NODO actual;
    NODO aux;
    if(!estaVacia(lista)){
        actual = lista->ini;
        if(actual == actual->sig){ //Solo hay un nodo
            free(actual);
            lista->ini = NULL;
            lista->fin = NULL;
        }
        else{
            actual = lista->ini->sig;
            while(actual != lista->ini){
                aux = actual;
                actual = actual->sig;
                free(aux);
            }
            free(lista->ini);
            lista->ini = NULL;
            lista->fin = NULL;
        }
        printf("\nLa lista se ha borrado de forma exitosa");
    }
    else{
        printf("\nLa lista esta vacia");
    }
}

void insertar(LISTA *lista, int dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;

    if(estaVacia(lista)){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        nuevo->sig = lista->ini->sig;
    }
    lista->ini->sig = nuevo;
    lista->fin = nuevo->sig;
}

void intercambiar(LISTA *lista, int dato, int nuevoDato){
    NODO aux = lista->ini;
    int exito = 0;
    if(estaVacia(lista)){
        printf("\nNo hay elementos en la lista");
        return;
    }
    if(aux == aux->sig){ //Solo un nodo
        if(aux->dato == dato){
            aux->dato = nuevoDato;
        }
        else{
            printf("\nEl dato no ha sido encontrado");
        }
        return;
    }
    else{
        do{
            if(aux->dato == dato){
                aux->dato = nuevoDato;
                exito = 1;
                break;
            }
            aux = aux->sig;
        }while(aux != lista->ini);
    }

    if(exito)
        printf("\nEl dato %d ha sido cambiado a %d", dato, nuevoDato);
    else
        printf("\nEl dato %d no fue encontrado en la lista", dato);
}
