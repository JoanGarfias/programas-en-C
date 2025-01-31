#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
	int dato;
	struct nodo *sig, *ant;
}NODO;

typedef struct cola{
	NODO *ini;
	NODO *fin;
}COLA;

COLA crearCola();
int estaVacia(COLA *);
void colar(COLA *, int);
int desencolarIni(COLA *);
int desencolarFin(COLA *);

int main(){
	COLA cola = crearCola();

	int i;
	for(i=10; i<=100; i+=10)
		colar(&cola, i);
	while(!estaVacia(&cola)){
		printf("%d ", desencolarIni(&cola));
	}
	printf("\n\n");
	for(i=10; i<=100; i+=10)
		colar(&cola, i);
	while(!estaVacia(&cola)){
		printf("%d ", desencolarFin(&cola));
	}
	printf("\n\n");

	return 0;
}

COLA crearCola(){
	COLA temp;
	temp.ini = NULL;
	temp.fin = NULL;
	return temp;
}

int estaVacia(COLA *cola){
	return cola->ini == NULL;
}

void colar(COLA *cola, int dato){
	NODO *aux = (NODO *) malloc(sizeof(NODO));
	if(aux==NULL)return;

	aux->dato = dato;
	aux->sig = NULL;

	if(estaVacia(cola)){
        aux->ant = NULL;
		cola->ini = aux;
		cola->fin = aux;
	}
	else{
        aux->ant = cola->fin;
		cola->fin->sig = aux;
		cola->fin = aux;
	}
	printf("%p %p %p %d||| %p %p %p ||| %p %p %p\n", aux, aux->ant, aux->sig, aux->dato,
        cola->ini, cola->ini->ant, cola->ini->sig,
        cola->fin, cola->fin->ant, cola->fin->sig);

}

int desencolarIni(COLA *cola){
	int val = -1;

	if(!estaVacia(cola)){
		NODO *aux = cola->ini;
		val = cola->ini->dato;
		cola->ini = cola->ini->sig;
		free(aux);
	}
	return val;
}

int desencolarFin(COLA *cola){
	int val = -1;

	if(!estaVacia(cola)){
		NODO *aux = cola->fin;
		val = cola->fin->dato;
		cola->fin = cola->fin->ant;
		free(aux);
		if(cola->fin == NULL){
            cola->ini = NULL;
		}
	}
	return val;
}
