#include<stdio.h>

long int sumaDivide(int, int);
int sumaRec(int);

int main(){
    int a,b;
    do{
        printf("\nIntroduce A:");
        scanf("%d", &a);
        printf("\nIntrodue B:");
        scanf("%d", &b);
    }while(a<0 || b<0);

    printf("%d + %d = %d", a,b,sumaDivide(a,b));

    return 0;
}

long int sumaDivide(int a, int b){
    int res = 0;
    res = sumaRec(a) + sumaRec(b);
    return res;
}

int sumaRec(int n){
    if(n==0)
        return 0;
    return  1 + sumaRec(n-1);
}