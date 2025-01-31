#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MARGEN_ERROR 999

#define GRADO 3

typedef struct lista{
    int *elem;
    int cant;
}LISTA;

LISTA analizarExpresion(LISTA);
LISTA hallarDivisores(int);

int main(){
    int i;
    LISTA exp;
    exp.elem = (int *) calloc(GRADO+1, sizeof(int));
    exp.cant = GRADO+1;

    for(i=0; i<=GRADO; i++){
        printf("x^%d | Elemento [%i]: ", GRADO-i, i+1);
        scanf("%d", &exp.elem[i]);
    }

    for(i=0; i<exp.cant; i++){
        printf("%d ", exp.elem[i]);
    }


    LISTA res = analizarExpresion(exp);

    printf("\n\n\n\n\n");

    for(i=0; i<res.cant; i++){
        if(res.elem[i] == MARGEN_ERROR){
            printf("\nSolucion %i: Solucion rara (Posible repeticion)", i+1);
            continue;
        }
        printf("\nSolucion %i : %d", i+1, res.elem[i]);
    }

    return 0;
}


LISTA analizarExpresion(LISTA exp){
    LISTA res;
    LISTA divisores = hallarDivisores(exp.elem[exp.cant-1]);
    res.elem = (int *) calloc(GRADO, sizeof(int));
    res.cant = 3;
    int i,j;
    double aux = 0.0;
    int sols = 0;
    int div;
    printf("\n\n");
    for(i=0; i<divisores.cant; i++){
        div = divisores.elem[i];
        printf("\nEstoy revisando el divisor %d", div);
        for(j=0; j<exp.cant; j++){
            printf("\n%d x %d^%d", exp.elem[j], div, exp.cant-j-1);
            aux = aux + exp.elem[j] * 1.0 * pow(div, exp.cant-j-1);
        }
        if(aux == 0.0){
            printf("\n%d si es solucion", div);
            res.elem[sols] = div;
            sols++;
        }
        else{
            printf("\n%d No es solucion, me dio %.1f", div,aux);
        }
        aux = 0.0;
    }

    if(sols != res.cant){
        for(i=sols; i<res.cant; i++){
            res.elem[i] = MARGEN_ERROR;
        }
    }

    return res;
}


LISTA hallarDivisores(int n){
    int i;
    LISTA lista;
    lista.elem = (int *) calloc(4, sizeof(int));
    lista.cant = 4;
    lista.elem[0] = 1;
    lista.elem[1] = -1;
    lista.elem[2] = n;
    lista.elem[3] = -n;
    if(n<0)
        n*=-1;
    for(i=2; i<=n/2; i++){
        if( n % i == 0){
            lista.elem = (int *) realloc(lista.elem, sizeof(int) * 1 * (lista.cant + 2) );
            lista.elem[lista.cant] = i;
            lista.elem[lista.cant+1] = -i;
            lista.cant+=2;
        }
    }

    printf("\nDivisores: \n");
    for(i=0; i<lista.cant; i++){
        printf("%d ", lista.elem[i]);
    }
    printf("\n\n");
    return lista;
}
