#include<stdio.h>
#include<math.h>

long int contDigs(long int n);
long int invertir(long int n, int tam);
int calcDifCeros(int, int);

int main(){
    long int n = 0;
    int i;
    printf("\nIntroduzca el numero a invertir: \n--> ");
    scanf("%ld", &n);

    int nInvertido = invertir(n, contDigs(n));
    printf("\n\nEl numero invertido es:");
    for(i=1; i<=calcDifCeros(nInvertido, n); i++)
        printf("0");
    printf("%d", nInvertido);

    return 0;
}

long int invertir(long int n, int tam){
    if(n<10) //Caso base
        return n;
    return (n%10) * (int)pow(10,tam-1) + invertir(n/10, tam-1); 
}

long int contDigs(long int n){
    if(n<10) //Caso base
        return 1;
    return 1 + contDigs(n/10);
}

int calcDifCeros(int x, int y){
    int dif=0;
    if (x==0 || y==0)
        return 0;
    while(contDigs(x) != contDigs(y)){
        x*=10;
        dif++;
    }
    return dif;
}