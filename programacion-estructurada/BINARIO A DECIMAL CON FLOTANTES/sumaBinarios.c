#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BASE 2

typedef struct{
    char entera[64];
    char flotante[64];
    int tieneFlotante;
}NUM;

typedef struct{
    int r;
    int ac;
}BIT;

int esFlotante(char *cad){
    int i;
    for(i=0; i<strlen(cad); i++){
        if(cad[i] == '.') return 1;
    }
    return 0;
}

NUM crearNumero(char *N1){
    NUM n1;
    int i;

    if(esFlotante(N1)){
        n1.tieneFlotante = 1;
        for(i=0; i<strlen(N1); i++){
            if(N1[i] == '.') break;
            n1.entera[i] = N1[i];
        }
        n1.entera[i]='\0';
        for(; i<strlen(N1); i++){
            n1.flotante[i-strlen(n1.entera) - 1] = N1[i];
        }
        n1.flotante[i-strlen(n1.entera) - 1] = '\0';
    }
    else{
        n1.tieneFlotante = 1;
        n1.flotante[0] = '\0';
    }
    return n1;
}

int main(){
    NUM n1, n2, r;
    int i;
    char N1[64], N2[64];
    n1.tieneFlotante = 0;
    n2.tieneFlotante = 0;
    printf("\nIntroduce el numero uno\n--> ");
    fflush(stdin);
    gets(N1);

    fflush(stdin);
    printf("\nIntroduce el numero dos\n--> ");
    gets(N2);
    fflush(stdin);


    n1 = crearNumero(N1);
    n2 = crearNumero(N2);

    printf("n1 = %s.%s\n", n1.entera, n1.flotante);
    printf("n2 = %s.%s", n2.entera, n2.flotante);

    BIT bit;
    bit.ac = 0;
    bit.r = 0;
    int acarreo = 0;
    char res[64];
    int cont = 0;

    r.tieneFlotante = 1;

    if(strlen(n2.flotante) > strlen(n1.flotante)){
        for(i=strlen(n2.flotante)-1; i<strlen(n1.flotante); i++){
            n2.flotante[i] = '0';
        }
    }

    for(i=strlen(n1.flotante)-1; i>= 0; i--){
        bit = sumarBinario(n1.flotante[i], n2.flotante[i]);
        cont++;
        res[cont] = bit.r;
    }

    return 0;
}
