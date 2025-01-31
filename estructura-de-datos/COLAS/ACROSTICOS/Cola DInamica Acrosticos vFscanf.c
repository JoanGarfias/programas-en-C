#include<stdio.h>
#include<stdlib.h>

struct nodo{
	char dato;
	struct nodo *sig;
};

typedef struct nodo* NODO;

void colar(NODO *, NODO *, char);
char desencolar(NODO *, NODO *);
int estaVacia(NODO *);

int main(){
	NODO ini = NULL;
	NODO fin = NULL;
	NODO aux = NULL;
	char letra;
	FILE *arc = fopen("poema.txt", "r");

	letra = getc(arc);
	colar(&ini, &fin, letra);

	while(!feof(arc)){
		if( (letra=getc(arc)) =='\n'){
			letra = getc(arc);
			colar(&ini, &fin, letra);
		}
	}

    aux = ini;
    while(aux != NULL){
        printf("%c", aux->dato);
        aux = aux->sig;
    }


	fclose(arc);
	return 0;
}

void colar(NODO *ini, NODO *fin, char dato){
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

char desencolar(NODO *ini, NODO *fin){
	char val = '\0';
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

void display(NODO *ini){
	NODO aux = *ini;
	while(aux != NULL){
		printf("%c", aux->dato);
		aux = aux->sig;
	}
}
