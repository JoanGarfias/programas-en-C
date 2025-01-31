#include<stdio.h>
#define MAXTAM 32

int estaVacia(int, int);
void colar(char [], int *, char);
int desencolar(char [], int *, int);
void display(char [], int, int);
void inverso(char [], int, int);

int main(){
    char cola[MAXTAM];
    int ini = 0;
    int fin = -1;
    
 	FILE *fp = fopen("poema.txt", "r");
	char leido;
	
	leido = fgetc(fp);
	
	if(leido != EOF){
		colar(cola, &fin, leido);
	}
	while(leido != EOF){
		leido = fgetc(fp);
		if(leido == '\n' && leido!=EOF){
			leido = fgetc(fp);
			colar(cola, &fin, leido);
		}
	}
	
	while(!estaVacia(ini, fin)){
		printf("%c", desencolar(cola, &ini, fin));
	}
	
	fclose(fp);

	return 0;
}

int estaVacia(int ini, int fin){
    return ini > fin;
}

void colar(char cola[], int *fin, char dato){
	if (*fin != MAXTAM-1){
		*fin = *fin + 1;
		cola[*fin] = dato;
	}
	else{
		printf("\nSe agrego uno de mas");
		return;
	}
}

int desencolar(char cola[], int *ini, int fin){
	char v = '\0';
	if(*ini > fin){
		printf("\nERROR: Cola vacia\n");
	}
	else{
        v = cola[*ini];
        *ini = *ini + 1;
	}
	return v;
}

void display(char cola[], int ini, int fin){
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

void inverso(char cola[], int ini, int fin){
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
