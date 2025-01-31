#include<stdio.h>

#define MAXTAM 50

typedef struct cola{
	int ini;
	int fin;
	int datos[MAXTAM];
}COLA;

COLA crearCola();
int estaVacia(COLA *);
int primero(COLA *);
int ultimo(COLA *);
void colar(COLA *, int);
int desencolar(COLA *);
int esprimo(int n){
	int i;
	for(i=2; i<=n/2; i++)
		if(n%i == 0)
			return 0;
	return 1;
}
void display(COLA *);


int main(){
	COLA cola = crearCola();

	int i;
	int lim = 50;
	for(i=2; i<=lim; i++){
		if(esprimo(i))
			colar(&cola, i);
	}

	printf("\nPrimero en la cola: %d", primero(&cola));
	printf("\nUltimo en la cola: %d\n\n", ultimo(&cola));

	printf("\n\nViendo la cola: \n");
    display(&cola);

	return 0;
}

COLA crearCola(){
	COLA temp;
	temp.ini = -1;
	temp.fin = -1;
	return temp;
}

int estaVacia(COLA *cola){
	return cola->ini == -1;
}

int primero(COLA *cola){
	if(!estaVacia(cola)){
		return cola->datos[cola->ini];
	}
}

int ultimo(COLA *cola){
	if(!estaVacia(cola)){
		return cola->datos[cola->fin];
	}
	return -1;
}

void colar(COLA *cola, int dato){
	if(cola->fin < MAXTAM){
		if(cola->ini == -1){
			cola->ini = 0;
		}
		cola->fin++;
		cola->datos[cola->fin] = dato;
	}else{
		printf("\nLa cola esta llena");
	}
}

int desencolar(COLA *cola){
	int val = -1;
	int i;
	if(!estaVacia(cola)){
		val = cola->datos[cola->ini];
		if(cola->fin == 0){
			cola->ini = -1;
			cola->fin = -1;
			return val;
		}
		for(i=1; i<=cola->fin; i++)
			cola->datos[i-1] = cola->datos[i];
		cola->fin--;
	}
	else{
		printf("\nLa cola ya esta vacia");
	}
	return val;
}

void display(COLA *cola){
    if(estaVacia(cola)){
        printf("\nNo puedo recorrer");
        return;
    }
    int aux = cola->ini;
    while(aux != cola->fin+1){
        printf("%d ", cola->datos[aux]);
        aux++;
    }
}
