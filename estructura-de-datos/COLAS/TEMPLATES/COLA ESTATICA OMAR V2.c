#include<stdio.h>
#define MAXTAM 32

int estaLlena(int);
int estaVacia(int, int);
void colar(int [], int *, int);
int desencolar(int [], int *, int);
void display(int [], int, int);
void inverso(int [], int, int);

int main(){
    int cola[MAXTAM];
    int ini = 0;
    int fin = -1;
    int i;
    for(i=10; i<=30; i+=10){
        colar(cola, &fin, i);
    }
    //printf("\nEsta llena: %d || fin: %d", estaLlena(fin), fin);

    printf("\n\nRecorrido secuencial: \n");
    display(cola, ini, fin);
    printf("\n\nRecorrido inverso: \n");
    inverso(cola, ini, fin);

    printf("\n\nDesencolar: \n");
    while(!estaVacia(ini, fin)){
        printf("%d ", desencolar(cola, &ini, fin));
    }
    printf("%d ", desencolar(cola, &ini, fin));

	return 0;
}

int estaLlena(int fin){
    return fin >= MAXTAM;
}

int estaVacia(int ini, int fin){
    return ini > fin;
}

void colar(int cola[], int *fin, int dato){
	//if (*fin != MAXTAM){
    if(!estaLlena(*fin)){
		*fin = *fin + 1;
		cola[*fin] = dato;
	}
	else{
		printf("\nSe agrego uno de mas");
		return;
	}
}

int desencolar(int cola[], int *ini, int fin){
	int v = -1;
	if(estaVacia(*ini, fin)){
		printf("\nERROR: Cola vacia\n");
	}
	else{
        v = cola[*ini];
        *ini = *ini + 1;
	}
	return v;
}

void display(int cola[], int ini, int fin){
    if(!estaVacia(ini, fin)){
        int aux = ini;
        while(aux != fin+1){
            printf("%d ", cola[aux]);
            aux++;
        }
    }
    else{
        printf("\nNo puedo hacer el recorrido");
    }
}

void inverso(int cola[], int ini, int fin){
    if(!estaVacia(ini, fin)){
        int aux = fin;
        while(aux != ini-1){
            printf("%d ", cola[aux]);
            aux--;
        }
    }
    else{
        printf("\nNo puedo hacer el recorrido");
    }
}
