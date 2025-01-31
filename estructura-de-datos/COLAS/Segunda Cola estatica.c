#include<stdio.h>

typedef struct cola{
    int inicio;
    int fin;
    int datos[32];
}COLA;

int estaVacia(COLA);
void colar(COLA *, int);
int desencolar(COLA *);
int primero(COLA );
int main(){
    COLA cola;
    cola.inicio = -1;
    cola.fin = -1;

    int i;
    for(i=0; i<10; i++){
        colar(&cola, i);
    }
    printf("\n\n\n");
    printf("\nEl primero en la cola es : %d\n\n", primero(cola));
    while(!estaVacia(cola)){
        printf("%d ", desencolar(&cola));
    }

    return 0;
}

int estaVacia(COLA cola){
    return cola.inicio == -1;
}

void colar(COLA *cola, int dato){
    if(cola->fin < 50){
        if(estaVacia(*cola)){
            cola->inicio = 0;
        }
        cola->fin++;
        cola->datos[cola->fin] = dato;
        return;
    }
    else{
        printf("\nLa cola esta llena");
    }
}

int desencolar(COLA *cola){
    int val = -1;
    int i;
    if(!estaVacia(*cola)){
        val = cola->datos[cola->inicio];
        if(cola->fin == 0){
            cola->inicio = -1;
            cola->fin = -1;
            return val;
        }
        for(i=1; i<=cola->fin; i++)
            cola->datos[i-1] = cola->datos[i];
        cola->fin--;
        if(cola->fin == -1)
            cola->inicio = -1;
            return val;
    }else{
        printf("\nLa cola esta vacia");
    }
}

int primero(COLA cola){
    if(!estaVacia(cola)){
        return cola.datos[cola.inicio];
    }
    else{
        printf("\nLa cola esta vacia y no puedo regresar el primero");
    }
}
