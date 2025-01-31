#include<stdio.h>

long int esprimo(int n, int cont);

int main(){
    int i = 0;

    for(i=2; i<=20; i++){
        printf("%i es ", i);
        printf(esprimo(i,2)? "primo\n" : "NO primo\n");
    }


    return 0;
}

long int esprimo(int n, int cont){
    if(cont > n / 2){
        return 1;
    }
    else{
        if(n % cont == 0)
            return 0;
        else 
            return esprimo(n, cont+1);
    }

}