#include<stdio.h>

int calcular(int a, int b);

int main(){
    int a;
    do{
        printf("\n\nIngrese dos valores\n--> ");
        scanf("%d", &a);
    }while(a<=0);

    printf("\n\nCombinaciones de suma posibles: %d", calcular(a,a));

    return 0;
}

int calcular(int n, int max) {
    if (n == 0) {
        return 1;
    }

    int total = 0;

    for (int i = 1; i <= max && i <= n; i++) {
        total += calcular(n - i, i);
    }

    return total;
}