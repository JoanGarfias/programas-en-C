#include<stdio.h>
#include<stdlib.h>

struct nodo{
	int dato;
	struct nodo *sig;
};

typedef struct nodo* NODO;

void colar(NODO *, NODO *, int);
int desencolar(NODO *, NODO *);
int estaVacia(NODO *);

int main(){
	NODO ini = NULL;
	NODO fin = NULL;
	int i;

	for(i=10; i<=100; i+=10){
		colar(&ini, &fin, i);
	}

	while(ini != NULL){
		printf("%d ", desencolar(&ini, &fin));
	}

}

void colar(NODO *ini, NODO *fin, int dato){
	NODO nuevo = (NODO) malloc(sizeof(struct nodo));
	if(nuevo==NULL)return;

	nuevo->dato = dato;
	nuevo->sig = NULL;

	if(*ini == NULL){
		*ini = nuevo;
		*fin = nuevo;
	}
	else{
		(*fin)->sig = nuevo;
		*fin = nuevo;
	}
}

int desencolar(NODO *ini, NODO *fin){
    printf("\nHola");
	int val = -1;
	if(ini == NULL){
		printf("\nLa cola esta vacia");
		return val;
	}
	NODO aux = *ini;
	val = aux->dato;
	(*ini) = (*ini)->sig;
	free(aux);

	if(*ini == NULL)
		*fin = NULL;

	return val;
}
