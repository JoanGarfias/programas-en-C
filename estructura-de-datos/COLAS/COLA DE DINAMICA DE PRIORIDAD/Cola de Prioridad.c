#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct persona{
	char nombre[32];
}PERSONA;

struct nodo{
	PERSONA dato;
    int prioridad;
	struct nodo *sig;
};

typedef struct nodo* NODO;

void colar(NODO *, NODO *, PERSONA, int);
PERSONA desencolar(NODO *, NODO *);
int estaVacia(NODO *);
PERSONA pedirPersona();

int main(){
	NODO ini = NULL;
	NODO fin = NULL;
	int op = 0, cont = 0;
	PERSONA pers;
    int priori = 0;
    NODO aux;
	do{
		printf("\n1) Agregar PERSONA");
		printf("\n2) Eliminar PERSONA");
		printf("\n3) Ver ultima persona agregada\n4) Ver lista de personas \n5)Salir\n--> ");
		fflush(stdin);
		scanf("%d", &op);
		if(op==5) break;
		switch(op){
			case 1:
                printf("\n\nIntroduce la prioridad: \n--> ");
                getchar();
                scanf("%d", &priori);
				colar(&ini, &fin, pedirPersona(), priori);
				printf("\n\nLa persona fue agregada con exito!");
				break;
			case 2:
				if(ini != NULL){
					pers = desencolar(&ini, &fin);
					printf("\n\nSe desencolo a %s", pers.nombre);
				}
				break;
			case 3:
				if(ini != NULL){
					pers = ini->dato;
					printf("\n\nLa persona es: %s", pers.nombre);
				}
				break;
            case 4:
                cont = 1;
                aux = ini;
                while(aux != NULL){
                    printf("\n\n%i) %s", cont, aux->dato.nombre);
                    aux = aux->sig;
                    cont+=1;
                }
				break;
		}
		printf("\n\n");
		system("PAUSE");
		system("CLS");
	}while(op!=5);
	free(ini);
	free(fin);
	free(aux);
	free(pers.nombre);
}

void colar(NODO *ini, NODO *fin, PERSONA dato, int nPrioridad){
	NODO nuevo = (NODO) malloc(sizeof(struct nodo));
    nuevo->prioridad = nPrioridad;
/*__ LISTA DE NODOS AUXILIARES __*/
	NODO ayu;
	NODO aux;
	NODO auxAnt;
/*_______________________________*/

	if(nuevo==NULL)return;

	nuevo->dato = dato;
	nuevo->sig = NULL;

	if(*ini == NULL){
		*ini = nuevo;
		*fin = nuevo;
	}
	else{
        aux = *ini;
        auxAnt = *ini;
        while(aux!=NULL && (aux->prioridad < nPrioridad) ){
            auxAnt = aux;
            aux = aux->sig;
        }
        if(aux == NULL){ //Es un nodo al ultimo
            (*fin)->sig = nuevo;
            *fin = nuevo;
            return;
        }
        else{
            if(aux == *ini){ //Es un nodo al inicio de la cola
                nuevo->sig = *ini;
                *ini = nuevo;
            }
            else{
                ayu = aux;
                auxAnt->sig = nuevo;
                aux = nuevo;
                aux->sig = ayu;
            }
        }
	}
}

PERSONA desencolar(NODO *ini, NODO *fin){
	PERSONA val = {""};
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

PERSONA pedirPersona(){
	PERSONA p;
    printf("\n\nIngrese el nombre\n--> ");
    getchar();
    scanf("%s", p.nombre);
	return p;
}
