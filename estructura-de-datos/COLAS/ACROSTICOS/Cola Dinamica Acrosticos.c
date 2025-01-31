#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct nodo{
	char dato;
	struct nodo *sig;
};

typedef struct nodo* NODO;

void colar(NODO *, NODO *, int);
char desencolar(NODO *, NODO *);
int estaVacia(NODO *);
void display(NODO *);

int main(){
	NODO ini = NULL;
	NODO fin = NULL;
	FILE *fp = fopen("poema.txt", "r");
	char leido;

	/*

	fgetc(fp)
	getc(fp)
	fscanf(fp, "%c%d%c%s")
	fgets()

	*/

	leido = fgetc(fp);
	if( ! feof(fp) ){
		colar(&ini, &fin, leido);
	}
	else{
		printf("\n\nEl archivo esta vacio");
		return 0;
	}

	while( !feof(fp) ){
		if(((leido=fgetc(fp))=='\n') && !feof(fp)){
			while(!isalpha((leido = fgetc(fp))) && !feof(fp)){
				leido = fgetc(fp);
			}
			colar(&ini, &fin, leido);
		}
	}



	printf("\n\nEl acrostico es: \n");
	NODO aux = ini;
	while(aux!=NULL){
		printf("%c", aux->dato);
		aux = aux->sig;
	}

	fclose(fp);
	return 0;
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
