#include<stdio.h>
#include<stdlib.h>
typedef struct nodo{
	int dato;
	struct nodo *sig;
}NODO;

typedef struct cola{
	NODO *ini;
	NODO *fin;
}COLA;

COLA crearCola();
int estaVacia(COLA *);
int primero(COLA *);
int ultimo(COLA *);
void colar(COLA *, int);
int desencolar(COLA *);

int main(){
	COLA cola = crearCola();
	
	int i;
	for(i=10; i<=100; i+=10)
		colar(&cola, i);
	
	while(!estaVacia(&cola)){
		printf("%d ", desencolar(&cola) );
	}
	
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

int primero(COLA *cola){
	if(!estaVacia(cola)){
		return cola->ini->dato;
	}
}

int ultimo(COLA *cola){
	if(!estaVacia(cola)){
		return cola->fin->dato;
	}
}

void colar(COLA *cola, int dato){
	
	NODO *nuevo = (NODO *) malloc(sizeof(NODO));
	if(nuevo==NULL)return;
	
	nuevo->dato = dato;
	nuevo->sig = NULL;
	
	if(estaVacia(cola)){
		cola->ini = nuevo;
		cola->fin = nuevo;
	}
	else{
		cola->fin->sig = nuevo;
		cola->fin = nuevo;
	}
}

int desencolar(COLA *cola){
	if(!estaVacia(cola)){
		int val = cola->ini->dato;
		NODO *aux = cola->ini;
		cola->ini = cola->ini->sig;
		free(aux);
		return val;
	}
	return -1;
}
