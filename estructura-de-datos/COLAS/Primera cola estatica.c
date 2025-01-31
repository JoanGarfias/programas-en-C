#include<stdio.h>
#include<stdlib.h>

typedef struct cola{
	int inicio;
	int final;
	int datos[100];
}COLA;

COLA crearCola();
int estaVacia(COLA *);
void colar(COLA *, int);
int desencolar(COLA *);
int tope(COLA *);

int main(){
	COLA cola = crearCola();
	
	colar(&cola, 10);
	colar(&cola, 20);
	colar(&cola, 30);
	
	printf("INICIO de Cola: %d\n\n", tope(&cola));
	while(!estaVacia(&cola)){
		printf("Elemento: %d\n", desencolar(&cola));
	}
	
	return 0;
}

COLA crearCola(){
	COLA temp;
	temp.inicio = -1;
	temp.final = -1;
	return temp;
}

int estaVacia(COLA *cola){
	return cola->inicio==-1;
}

void colar(COLA *cola, int dato){
	if(cola->final < 100){
		if(estaVacia(cola)){
			cola->inicio = 0;
		}
		cola->final++;
		cola->datos[cola->final] = dato;
		return;
	}
	else{
		printf("\nCOLA LLENA");
		return;
	}
}

int desencolar(COLA *cola){
	int i;
	int val = -1;
	if(!estaVacia(cola)){
		val = cola->datos[cola->inicio];
		printf("Se desencolo %d\n", cola->datos[cola->inicio]);
		if(cola->final == 0){
			cola->inicio = -1;
			cola->final = -1;
			return val;
		}
		
		for(i=1; i<=cola->final; i++){
			cola->datos[i-1] = cola->datos[i];
		}
		cola->final--;
		if(cola->final == -1){
			cola->inicio = -1;
		}
	}
	else{
		printf("\nPILA LLENA");
	}
	return val;
}

int tope(COLA *cola){
	if(!estaVacia(cola)){
		return cola->datos[cola->inicio];
	}
	printf("\nERROR: No puedo dar el tope");
	return -1;
}
