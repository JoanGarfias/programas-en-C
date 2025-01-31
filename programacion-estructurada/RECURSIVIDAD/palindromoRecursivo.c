#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int palindromo(char *, int, int);

int main(){
    char *cad = (char *) calloc(380, sizeof(char));

    printf("\n\nIntroduzca una palabra: \n--> ");
    fgets(cad, 380, stdin);
    
    if(palindromo(cad, 0, (int)strlen(cad)-1)){
        printf("\n%s \n\nEs una palabra PALINDROMA", cad);
    }
    else{
        printf("\n%s \n\nNO es una palabra PALINDROMA", cad);
    }

    free(cad);
    return 0;
}

int palindromo(char *cad, int aux, int tam){
    if(!isalpha(cad[aux]) && !isalpha(cad[tam-1])){
        return palindromo(cad, aux+1, tam-1);
    }
    else if(!isalpha(cad[aux])){
        return palindromo(cad, aux+1, tam);
    }
    else if(!isalpha(cad[tam-1])){
        return palindromo(cad, aux, tam-1);
    }
    else if(tam <= 1){
        return 1;
    }
    else if(toupper(cad[aux]) != toupper(cad[tam-1])){
        return 0;
    }
    return palindromo(cad, aux+1, tam-1);
}