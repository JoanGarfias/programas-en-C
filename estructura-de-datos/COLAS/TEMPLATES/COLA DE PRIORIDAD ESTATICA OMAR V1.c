#include<stdio.h>
#include<stdlib.h>

#define MAXTAM 15

typedef struct n{
    int num;
    int prioridad;
}NUMERO;

int estaLlena(int);
int estaVacia(int, int);
void colar(NUMERO [], int *, NUMERO);
NUMERO desencolar(NUMERO [], int *, int *);
void display(NUMERO [], int, int);
void inverso(NUMERO [], int, int);
int estaLlena(int);
int peek(NUMERO [], int, int);
NUMERO pedirN();

int main(){
    NUMERO cola[MAXTAM];
    int ini = 0;
    int fin = -1;
    int i;
    int op;
    int dato = 0;
    int ind = 0;
    NUMERO n;

    do{
        printf("\n\n1) Encolar \n\n2) Desencolar \n\n3) Mostrar \n\n4) Ver proximo a salir \n\n5) Salir\n--> ");
        fflush(stdin);
        scanf("%d", &op);
        if(op==5) break;

        switch(op){
        case 1:
            //if !estaLlena
            printf("\nSeleccion: Colar \n\n");
            colar(cola, &fin, pedirN());
            break;
        case 2:
            n = desencolar(cola, &ini, &fin);
            if(n.prioridad != -1){
                printf("Desencolado: %d con prioridad %d", n.num, n.prioridad);
            }
            break;
        case 3:
            printf("\n\nRecorrido: \n");
            display(cola, ini, fin);
            break;
        case 4:
            if((ind = peek(cola, ini, fin) ) != -1){
                printf("\n\nEl proximo elemento a salir es: %d con prioridad %d", cola[ind].num, cola[ind].prioridad);
            }
            else{
                printf("\n\nNo se puede mostrar");
            }
            break;
        default:
            printf("\n\nOpcion no valida");
            break;
        }
        printf("\n\n");
        system("PAUSE");
        system("CLS");
    }while(op!=5);


	return 0;
}

int estaLlena(int fin){
    return fin >= MAXTAM - 1;
}

int estaVacia(int ini, int fin){
    return ini > fin;
}

void colar(NUMERO cola[], int *fin, NUMERO dato){
	if (!estaLlena(*fin)){
		*fin = *fin + 1;
		cola[*fin] = dato;
	}
	else{
		printf("\nNo se puede agregar el elemento: Cola llena");
		return;
	}
}

NUMERO desencolar(NUMERO cola[], int *ini, int *fin){
	NUMERO v = {-1,-1};
	int i;
	int pPriori = *ini;
	//printf("\nIni: %d Fin: %d", *ini, *fin);
	if(estaVacia(*ini,*fin)){
		printf("\nERROR: Cola vacia\n");
	}
	else{
        v = cola[*ini];
        if(*ini==*fin){
            *ini = *ini + 1;
            return cola[*ini-1];
        }
        int PR = v.prioridad;

        for(i=*ini; i<=(*fin); i++){
            if(cola[i].prioridad > PR){
                pPriori = i;
            }
        }

        v = cola[pPriori];
        cola[pPriori] = cola[*ini];

        *ini = *ini + 1;
	}
	//printf("\nIndice Prioritario: %d ||| Ini: %d Fin: %d",pPriori, *ini, *fin);
	return v;
}

void display(NUMERO cola[], int ini, int fin){
    if(!estaVacia(ini, fin)){
        int aux = ini;
        while(aux != fin+1){
            printf("\nNumero: %d | Prioridad: %d", cola[aux].num, cola[aux].prioridad);
            aux++;
        }
    }
    else{
        printf("\nNo puedo hacer el recorrido porque la cola esta vacia");
    }
}

void inverso(NUMERO cola[], int ini, int fin){
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

NUMERO pedirN(){
    NUMERO n;
    fflush(stdin);
    printf("\n\nIntroduzca el dato: \n--> ");
    scanf("%d", &n.num);
    printf("\n\nIntroduzca la prioridad: \n--> ");
    fflush(stdin);
    scanf("%d", &n.prioridad);
    return n;
}

int peek(NUMERO cola[], int ini, int fin){
    int i;
    int may = ini;
    int pPriori = cola[ini].prioridad;
    if(estaVacia(ini, fin)){
        printf("\n\nLa cola esta vacia");
        return -1;
    }

    if(ini == fin){
        return may;
    }

    for(i=ini+1; i<=fin; i++){
        if(pPriori < cola[i].prioridad){
            pPriori = cola[i].prioridad;
            may = i;
        }
    }
    return may;
}
