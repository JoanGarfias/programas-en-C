#include<stdio.h>
#include<stdlib.h>

#define MAXTAM 5

int estaLlena(int);
int estaVacia(int, int);
void colar(int [], int *, int);
int desencolar(int [], int *, int);
void display(int [], int, int);
void inverso(int [], int, int);
int estaLlena(int);

int main(){
    int cola[MAXTAM];
    int ini = 0;
    int fin = -1;
    int i;
    int op;
    int dato = 0;
    do{
        printf("\n\n1) Encolar \n\n2) Desencolar \n\n3) Mostrar \n\n4) Salir\n--> ");
        fflush(stdin);
        scanf("%d", &op);
        if(op==4) break;

        switch(op){
        case 1:
            //if !estaLlena
            printf("\nSeleccion: Colar \n\nIntroduzca el dato a colar: \n--> ");
            scanf("%d", &dato);
            colar(cola, &fin, dato);
            break;
        case 2:
            printf("Desencolado: %d", desencolar(cola, &ini, fin));
            break;
        case 3:
            printf("\n\nRecorrido: \n");
            display(cola, ini, fin);
            break;
        default:
            printf("\n\nOpcion no valida");
            break;
        }
        printf("\n\n");
        system("PAUSE");
        system("CLS");
    }while(op!=4);


	return 0;
}

int estaLlena(int fin){
    return fin >= MAXTAM - 1;
}

int estaVacia(int ini, int fin){
    return ini > fin;
}

void colar(int cola[], int *fin, int dato){
	if (!estaLlena(*fin)){
		*fin = *fin + 1;
		cola[*fin] = dato;
	}
	else{
		printf("\nNo se puede agregar el elemento: Cola llena");
		return;
	}
}

int desencolar(int cola[], int *ini, int fin){
	int v = -1;
	if(estaVacia(*ini,fin)){
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
        printf("\nNo puedo hacer el recorrido porque la cola esta vacia");
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
