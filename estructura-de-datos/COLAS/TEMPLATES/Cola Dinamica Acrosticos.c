#include<stdio.h>
#include<stdlib.h>

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
	
	leido = fgetc(fp);
	
	if(leido != EOF){
		colar(&ini, &fin, leido);
	}
	else{
		printf("ERROR: El archivo esta vacio");
		return 0;
	}
	
	while(leido != EOF){
		leido = fgetc(fp);
		if(leido == '\n' && leido!=EOF){
			leido = fgetc(fp);
			colar(&ini, &fin, leido);
		}
	}
	printf("\n\nEl acrostico es: \n");
	display(&ini);
	
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
