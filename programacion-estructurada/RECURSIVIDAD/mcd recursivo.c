#include<stdio.h>

long int mcd(int a, int b);
long int mcdIte(int a, int b);

int main(){
    int n1,n2;
    printf("\n\nIntroduce dos numeros: \n\n--> ");
    scanf("%d", &n1);
    printf("\n--> ");
    scanf("%d", &n2);
    printf("\n\nEl MCD de %d y %d es: \n\n", n1, n2);
    printf("Recursivo: %d \n", mcd(n1, n2));
    printf("Iterativo: %d \n\n", mcdIte(n1,n2));

    return 0;
}

long int mcd(int a, int b){
    return (b!=0)? mcd(b, a%b) : a;
}

long int mcdIte(int a, int b){
    int temp;
    /*
    while(b != 0){
        temp = b;
        b = a % b;
        a = temp;
    }*/
    while(b!=0){
        temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}
