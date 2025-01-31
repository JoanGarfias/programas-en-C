#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct list{
    int *elem;
    int n;
}LISTA;

LISTA divisores(int);
LISTA soluciones(LISTA, LISTA);
int esSolucion(LISTA, int);

int main(){
    LISTA exp, divs, sols;
    int grado, i;

    printf("\nIntroduzca el grado: \n--> ");
    scanf("%d", &grado);
    printf("\n\n\n");

    exp.elem = (int *) calloc(grado+1, sizeof(int));
    exp.n = grado+1;

    for(i=0; i<=grado; i++){
        printf("x^%i :\n", grado-i);
        scanf("%d", &exp.elem[i]);
    }

    printf("\n\nPolinomio: ");
    for(i=0; i<=grado; i++){
        printf("%dx^%i ", exp.elem[i], grado-i);
    }

    printf("\n\nBuscare divisores de %d", exp.elem[grado]);
    divs = divisores( exp.elem[grado] );

    printf("\n\nPosibles soluciones : \n");
    for(i=0; i<divs.n; i++){
        printf("%d ", divs.elem[i]);
    }

    sols = soluciones(exp, divs);
    printf("\n\n\nSe encontraron las siguientes soluciones: \n");
    for(i=0; i<sols.n; i++){
        printf("Solucion %i : %d \n", i+1, sols.elem[i]);
    }

    return 0;
}

LISTA divisores(int num){
    LISTA divs;
    if(num<0){
        num*=-1;
    }
    if(num==0){
        return (LISTA) {NULL, 0};
    }
    divs.n = 4;
    divs.elem = (int *) calloc(4, sizeof(int));
    divs.elem[0]=1;     divs.elem[1]=-1;
    divs.elem[2]=num;   divs.elem[3]=-num;
    int i;
    for(i=2; i<=num/2; i++){
        if(num % i == 0){ //Hay otro divisor
            divs.elem = (int *) realloc(divs.elem, sizeof(int) * (divs.n + 2) );
            divs.elem[divs.n] = i;
            divs.elem[divs.n + 1] = -i;
            divs.n = divs.n + 2;
        }
    }
    return divs;
}

LISTA soluciones(LISTA exp, LISTA divs){
    int i;
    LISTA sols;
    sols.elem = (int *) calloc(1, sizeof(int));
    sols.n = 0;
    printf("\n\n");
    for(i=0; i<divs.n; i++){
        if(esSolucion(exp, divs.elem[i])){
            sols.elem[sols.n] = divs.elem[i];
            sols.n++;
            sols.elem = (int *) realloc(sols.elem, sizeof(int) * (sols.n + 1));
        }
    }
    return sols;
}

int esSolucion(LISTA exp, int div){
    int i;
    long int acum = 0;

    for(i=0; i<exp.n-1; i++){
        acum += exp.elem[i] * (int) pow(div, exp.n-i-1);
    }
    acum += exp.elem[i];
    if(acum==0){
        printf("%d es solucion, me dio 0 \n", div);
    }
    else{
        printf("%d no es solucion, me dio %ld\n", div, acum);
    }

    return acum == 0;
}
