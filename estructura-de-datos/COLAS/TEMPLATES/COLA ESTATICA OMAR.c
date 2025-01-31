#include<stdio.h>
#define MAXTAM 32
typedef struct cola{
	int ini;
	int fin;
	int datos[MAXTAM];
}COLA;

COLA crearCola();
int estaVacia(COLA *);
void colar(COLA *, int);
int desencolar(COLA *);
int primero(COLA *);
int ultimo(COLA *);

int main(){
	COLA cola = crearCola();
	int i;
	for(i=1; i<=9; i++)
		colar(&cola, i);

	while(!estaVacia(&cola)){
		printf("%d ", desencolar(&cola));
	}
	printf("\n\n");
	for(i=9; i>=0; i--)
		colar(&cola, i);

	while(!estaVacia(&cola)){
		printf("%d ", desencolar(&cola));
	}

	return 0;
}

COLA crearCola(){
	COLA temp;
	temp.ini = 0;
	temp.fin = -1;
	return temp;
}

int estaVacia(COLA *cola){
	return cola->ini > cola->fin;
}

void colar(COLA *cola, int dato){
	if (cola->fin != MAXTAM-1){
		cola->fin++;
		cola->datos[cola->fin] = dato;
	}
	else{
		printf("\nSe agrego uno de mas");
		return;
	}
}

int desencolar(COLA *cola){
	int v = -1;
	if(!estaVacia(cola)){
		v = cola->datos[cola->ini];
		cola->ini++;
	}
	else{
        if(cola->ini > cola->fin){
            cola->fin = -1;
            cola->ini = 0;
        }
		printf("\n\nCola vacia");
	}
	return v;
}
