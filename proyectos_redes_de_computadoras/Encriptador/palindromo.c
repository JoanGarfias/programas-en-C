#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int noEsNumero(char *num){
    int i;
    for(i=0; num[i]!='\0'; i++){
        if(num[i]<'0' || num[i]>'9'){
            return 1;
        }
    }
    return 0;
}


int esPalindromo(int n){
    int reverso = 0, original = n;
    while(n > 0){
        reverso = reverso * 10 + n % 10;
        n /= 10;
    }
    return original == reverso;
}


int obtenerReverso(int numero){
    int reverso = 0;
    while(numero > 0){
        reverso = reverso * 10 + numero % 10;
        numero /= 10;
    }
    return reverso;
}

int main(int argc, char *argv[]){
    char num[64];
    int i;
    int contador = 0;
    int numero_inicial = 0;
    int numero_final = 0;
    int numero_actual = 0;
    int reverso = 0;

    for(i=0; i<64; i++){
        num[i] = '\0';
    }
    printf("Ingrese un numero palindromo: ");
    scanf("%s", num);

    while(noEsNumero(num)){
        printf("Ingrese un numero palindromo: ");
        scanf("%s", num);
        printf("El numero ingresado no es un numero\n");
        return 1;
    }

    numero_inicial = atoi(num);
    numero_actual = numero_inicial;

    while(!esPalindromo(numero_actual)){
        numero_actual = numero_actual;
        reverso = obtenerReverso(numero_actual);
        numero_actual = numero_actual + reverso;
        contador++;
    }

    numero_final = numero_actual;
    printf("Ha tomado %d intentos llegar al palindromo\n", contador);
    printf("El numero inicial es %d y el numero final es %d\n", numero_inicial, numero_final);
}
