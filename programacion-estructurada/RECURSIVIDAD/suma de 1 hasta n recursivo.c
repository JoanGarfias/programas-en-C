#include<stdio.h>

long int suma(long int);

int main(){
    int val = 100;
    printf("\nLa suma que hay entre 1 y %d es: \n", val);
    printf("%d", suma(val));

    return 0;
}

long int suma(long int n){
    if(n==1)
        return n;
    return n + (suma(n-1));
}