#include<stdio.h>
#include<stdlib.h>

#define HORAMIN 8
#define HORAMAX 18

typedef struct act{
	char nombre[32];
	char lugar[32];
	int hora;
}ACT;

struct nodo{
	ACT dato;
	struct nodo *sig;
};

typedef struct nodo* NODO;

void colar(NODO *, NODO *, ACT);
ACT desencolar(NODO *, NODO *);
int estaVacia(NODO *);
ACT pedirActividad();
void cargarDatos(NODO *, NODO *);
void guardarDatos(NODO *, NODO *);

int main(){
	NODO ini = NULL;
	NODO fin = NULL;
	int op = 0, cont = 0;
	ACT act;
    NODO aux;
	do{
		printf("\n1) Agregar actividad");
		printf("\n2) Eliminar actividad (realizada)");
		printf("\n3) Ver ultima actividad\n4) Ver lista de actividades \n5)Salir \n--> ");
		fflush(stdin);
		scanf("%d", &op);
		if(op==5) break;
		switch(op){
			case 1:
				colar(&ini, &fin, pedirActividad());
				printf("\n\nLa actividad fue agregada con exito!");
				break;
			case 2:
				if(ini != NULL){
					act = desencolar(&ini, &fin);
					printf("\n\nRealizaste %s en %s a las %d horas",
						act.nombre, act.lugar, act.hora);
				}
				break;
			case 3:
				if(ini != NULL){
					act = ini->dato;
					printf("\n\nTu siguiente actividad es %s en %s a las %d horas",
						act.nombre, act.lugar, act.hora);
				}
				break;
            case 4:
                cont = 1;
                aux = ini;
                while(aux != NULL){
                    printf("\n\n%d : Actividad: %s\nLugar: %s\nHora: %d", cont, aux->dato.nombre, aux->dato.lugar, aux->dato.hora);
                    aux = aux->sig;
                    cont+=1;
                }
				break;
		}
		printf("\n\n\n");
		system("PAUSE");
		system("CLS");
	}while(op!=5);

}

void colar(NODO *ini, NODO *fin, ACT dato){
	NODO nuevo = (NODO) malloc(sizeof(struct nodo));

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
        while(aux!=NULL && (aux->dato.hora < dato.hora) ){
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

ACT desencolar(NODO *ini, NODO *fin){
    printf("\nHola");
	ACT val = {" "," ", 0};
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

ACT pedirActividad(){
	ACT act;
	printf("\n\nSolo puedes registrar actividades entre las 8 y las 18 horas");
	printf("\nNombre de la actividad: \n--> ");
    fflush(stdin);
	fgets(act.nombre, 32, stdin);
	act.nombre[(int)strlen(act.nombre)-1] = '\0';
	fflush(stdin);
	printf("\nLugar de la actividad: \n--> ");
	fflush(stdin);
	scanf("%s", act.lugar);
	do{
        printf("\nHorario de la actividad: \n--> ");
        fflush(stdin);
        scanf("%d", &act.hora);
	}while(act.hora < 8 || act.hora > 18);
	return act;
}

void cargarDatos(NODO *ini, NODO *fin){
    FILE *fp = fopen("act.txt", "r");

    char *nom = (char * ) calloc(32, sizeof(char));
    char *lugar = (char * ) calloc(32, sizeof(char));
    int hora = 0;
    char aux = '\0';
    int i = 0;
    ACT temp;

    while(!feof(fp)){
            fflush(stdin);
        fscanf(fp, "%d %s", &hora, lugar);
        while((aux=fgetc(fp)) != '\n' ){
            nom[i] = aux;
            i++;
        }
        nom[i]='\0';
        strcpy(temp.nombre, nom);
        strcpy(temp.lugar, lugar);
        temp.hora = hora;
        colar(ini, fin, temp);
        nom[0] = '\0';
    }
    fclose(fp);
}

void guardarDatos(NODO *ini, NODO *fin){
    ACT temp;
    FILE *fp = fopen("act.txt", "w+");

    while(ini != NULL){
        temp = desencolar(ini, fin);
        fprintf(fp, "%d %s", temp.hora, temp.lugar);
        fputs(temp.nombre, fp);
    }
    printf("\n\nDatos guardados exitosamente...");
    fclose(fp);
    return;
}
