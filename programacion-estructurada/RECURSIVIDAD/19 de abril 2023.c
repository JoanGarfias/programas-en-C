#include<stdio.h>

long int fib(long int n);
long int fibIte(long int pos);

int main(){
    int lim = 0;
    long int i;
    int temp=0, act=0, sig=1;
    printf("\n\nIntroduce una posicion: \n\n--> ");
    scanf("%d", &lim);
    printf("\n\nFibonaci en posicion %d\n\n", lim);
    //printf("Recursivo: %d \n", fib(lim));
    printf("Iterativo: %d ", fibIte(lim));

    return 0;
}

long int fib(long int n){
    return (n<2)? n : fib(n-1) + fib(n-2);
}

long int fibIte(long int pos){
    int temp=0, act=0, sig=1,i;
    for(i=0; i<pos; i++){
        temp = act;
        act = sig;
        sig = sig + temp;
    }
    return act;
}
