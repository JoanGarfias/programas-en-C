/*
Demuestre por inducción que la función Q(n)=1^2+2^2+3^2+…+n^2
puede expresarse como Q(n) = n(n+1) (2n+1) / 6
*/

#include<stdio.h>
#include<math.h>

int function(int n);

int main(){
    int n;
    int res = 0;
    printf("Introduzca n: ");
    scanf("%d", &n);

    res = n * (n+1) * (2*n+1) / 6;

    printf("Resultado por formula: %d", res);
    printf("\nResultado por recursion: %d", function(n));

    return 0;
}

int function(int n){
    if(n==1)
        return n;
    return (int)pow(n,2) + function(n-1); 
}