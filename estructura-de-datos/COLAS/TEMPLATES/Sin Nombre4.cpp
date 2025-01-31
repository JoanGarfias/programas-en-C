#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


typedef struct nodo{
	char dato;
	struct nodo *sig;
}NODO;

COLA crearCola();
int estaVacia(NODO *);
char primero(COLA *);
char ultimo(COLA *);
void colar(COLA *, char);
char desencolar(COLA *);
void display(COLA *);

int main(){
	COLA cola = crearCola();
	FILE *fp = fopen("poema.txt", "r");
	char leido;
	
	leido = fgetc(fp);
	
	if(leido != EOF){
		colar(&cola, leido);
	}
	else{
		printf("ERROR: El archivo esta vacio");
		return 0;
	}
	
	while(leido != EOF){
		leido = fgetc(fp);
		if(leido == '\n' && leido!=EOF){
			leido = fgetc(fp);
			colar(&cola, leido);
		}
	}
	printf("\n\nEl acrostico es: \n");
	display(&cola);
	
	fclose(fp);
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

char primero(COLA *cola){
	if(!estaVacia(cola)){
		return cola->ini->dato;
	}
}

char ultimo(COLA *cola){
	if(!estaVacia(cola)){
		return cola->fin->dato;
	}
}

void colar(COLA *cola, char dato){
	
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

char desencolar(COLA *cola){
	if(!estaVacia(cola)){
		char val = cola->ini->dato;
		NODO *aux = cola->ini;
		cola->ini = cola->ini->sig;
		free(aux);
		return val;
	}
	return -1;
}

void display(COLA *cola){
	NODO *aux = cola->ini;
	while(aux != NULL){
		printf("%c", aux->dato);
		aux = aux->sig;
	}
}
