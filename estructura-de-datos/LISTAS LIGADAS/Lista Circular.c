#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct nodo{
    char *dato;
    struct nodo *sig;
};
typedef struct nodo * NODO;

int estaVacia(NODO *);
void insertar(NODO *, char *);
char *eliminar(NODO *);

void mover(NODO );

int main(){

    NODO lista = NULL;

    double v_alt = 0.0;
    double barrera = 0.6;

    insertar(&lista, "Joan");
    insertar(&lista, "Victor");
    insertar(&lista, "Mara");
	insertar(&lista, "Gerson");
	insertar(&lista, "Patata");

    mover(lista);
    srand(time(NULL));

    if(lista != NULL){
        while(lista->sig != lista){
            v_alt = (double) rand() / RAND_MAX;
            if(v_alt > barrera){
                printf("\nEl jugador %s perdio", eliminar(&lista));
                mover(lista);
                sleep(1.5);
            }
            lista = lista->sig;
            printf("\nLa papa se quema... ");
            sleep(0.7);
        }
        printf("\n\nTenemos un ganador! \nFelicidades a %s por ganar!", lista->dato);
    }

    return 0;
}

int estaVacia(NODO *nodo){
    return *nodo == NULL;
}

void insertar(NODO *ini, char *dato){
    NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->dato = dato;

    if(estaVacia(ini)){
        *ini = nuevo;
        (*ini)->sig = nuevo;
    }
    else{
        nuevo->sig = (*ini)->sig;
        (*ini)->sig = nuevo;
    }
}

char* eliminar(NODO *ini){
    char * jug;
    int i;
    NODO aux = *ini;
    if(*ini == NULL){
        jug = (*ini)->dato;
        printf("\n\nTenemos un ganador! \nFelicidades a %s por ganar!", (*ini)->dato);
        return jug;
    }
    else{
        if(aux == aux->sig){
            jug = aux->dato;
            free(aux);
            *ini = NULL;
        }
        else{
            aux = aux->sig;
            (*ini)->sig = aux->sig;
            jug = aux->dato;
            free(aux);
        }
    }
    return jug;
}

void mover(NODO ini){
	NODO aux = ini;
	do{
		//printf("%d ",lista->valor);
		ini = ini->sig;
	}while(ini!=aux);
}
