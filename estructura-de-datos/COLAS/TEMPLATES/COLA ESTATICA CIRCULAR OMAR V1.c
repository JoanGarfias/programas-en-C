#include<stdio.h>
#include<stdlib.h>

#define MAXTAM 5

typedef struct num{
    int numero;
    int prioridad;
}NUMERO;

int estaLlena(int);
int estaVacia(int);
void colar(NUMERO [], int *, int *, NUMERO);
int desencolar(NUMERO [], int *, int *);
void display(NUMERO [], int, int);
void inverso(NUMERO [], int, int);
int estaLlena(int);
NUMERO pedirN();
int peek(NUMERO [], int);

int main(){
    NUMERO cola[MAXTAM];
    int ini = 0;
    int n = 0;
    int i;
    int op;
    int dato = 0;
    int nPriori = 0;
    do{
        printf("\n\n1) Encolar \n\n2) Desencolar \n\n3) Mostrar \n\n4) Salir\n--> ");
        fflush(stdin);
        scanf("%d", &op);
        if(op==4) break;

        switch(op){
        case 1:
            //if !estaLlena
            colar(cola, &ini, &n, pedirN());
            break;
        case 2:
            nPriori = desencolar(cola, &ini, &n);
            printf("\n\nEl dato desencolado con mayor prioridad es: \n");
            printf("\n%d con prioridad %d", cola[nPriori].numero, cola[nPriori].prioridad);
            break;
        case 3:
            printf("\n\nRecorrido: \n");
            display(cola, ini, n);
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

int estaLlena(int n){
    return n >= MAXTAM;
}

int estaVacia(int n){
    return n == 0;
}

void colar(NUMERO cola[], int *ini, int *n, NUMERO dato){
	int pos = -1;
	if (!estaLlena(*n)){
		pos = (*ini + *n) % MAXTAM;
		cola[pos] = dato;
		*n = *n + 1;
	}
	else{
		printf("\nNo se puede agregar el elemento: Cola llena");
		return;
	}
}

int desencolar(NUMERO cola[], int *ini, int *n){
	NUMERO v = {-1,-1};
	int pPriori = 0;
	int i = 0;
	int j = 0;
	if(*n == 0){
		printf("\nERROR: Cola vacia\n");
		return 0;
	}
	else{
        if(*n==1){
            *n = *n-1;
            pPriori = *ini;
            *ini = (*ini + 1) % MAXTAM;
            return pPriori;
        }
        else{
            v = cola[*ini];
            for(i=0; i<n-1; i++){
                if(v.prioridad < cola[i].prioridad){
                    v.prioridad = cola[i].prioridad;
                }
            }

            for(i=(*n)-1; i>pPriori; i--){
                cola[i-1] = cola[i];
            }
            *ini = (*ini + 1) % MAXTAM;
            *n = *n - 1;
             printf("\n%d", pPriori);
        return pPriori;
	}
}

void display(NUMERO cola[], int ini, int n){
    if(!estaVacia(n)){
        int aux = ini;
        int tam = n;
        while(n != 0){
            printf("Numero: %d Prioridad: %d\n", cola[aux].numero, cola[aux].prioridad);
            aux++;
            if(aux == MAXTAM){
                aux = 0;
            }
            n--;
        }
    }
    else{
        printf("\nNo puedo hacer el recorrido porque la cola esta vacia");
    }
}

void inverso(NUMERO cola[], int ini, int n){
    if(!estaVacia(n)){
        int aux = ini;
        while(aux != 0){
            if(aux >= MAXTAM)
                aux = 0;
            printf("%d ", cola[aux]);
            aux--;
        }
    }
    else{
        printf("\nNo puedo hacer el recorrido");
    }
}

NUMERO pedirN(){
    NUMERO temp;
    fflush(stdin);
    printf("\n\nIngrese el dato: \n");
    scanf("%d", &temp.numero);
    printf("\n\nIngrese la prioridad; \n");
    scanf("%d", &temp.prioridad);
    return temp;
}

int peek(NUMERO cola[], int n){
    int pPriori = 0;
    int i;
    if(estaVacia(n)){
        printf("\n\nLa cola esta vacia");
        return 0;
    }
    else{
        if(n==1){
            return 0;
        }
        else{
            i = 0;
            while(i < n-1){
                if(cola[i].prioridad > cola[i+1].prioridad){
                    pPriori = i;
                }
                else{
                    pPriori = i+1;
                }
                i++;
            }
        }
    }
    return pPriori;
}
