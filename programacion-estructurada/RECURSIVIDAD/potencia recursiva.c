#include<stdio.h>

long int potenciar(long int, long int);

int main(){
    int a=0, b=0;

    do{
    printf("\nIntroduzca la base: ");
    scanf("%d", &a);
    printf("\nIntroduzca el exponente");
    scanf("%d", &b);
    }while(a<=0 || b<0);

    printf("%d elevado a la %d potencia es:\n--> %d", a,b, potenciar(a,b));

    return 0;
}

long int potenciar(long int a, long int b){
    if(b == 0)
        return 1;
    return a * potenciar(a, b-1);
}