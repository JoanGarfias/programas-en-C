#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

typedef struct pass{
    int min;
    int may;
    int simb;
    int nums;
}PASS;

typedef struct randList{
    int *lista;
    int cant;
}LISTA;

PASS crearPass();
void generar(PASS, char **, int);
LISTA listaRand(PASS);
void verSeguridad();

int main(){
    int size = 10;
    int op;

    PASS ajustes = crearPass();
    ajustes.min = 1;
    ajustes.may = 1;
    ajustes.nums = 1;
    ajustes.simb = 0;
    char *pass = (char *) calloc(size, sizeof(char));
    char aux;
    do{
        fflush(stdin);
        printf("\n\n__________________GENERADOR DE CONTRASENIAS_____________________");
        printf("\n\n_____________________ v1.0 by joansk9 __________________________");
        printf("\n\n        _________ MENU DE SELECCION __________");
        printf("\n\n\t 1) Generar nueva password");
        printf("\n\t 2) Cambiar tamanio de password");
        printf("\n\t 3) Ajustes de password");
        printf("\n\t 4) Ver seguridad de un password");
        printf("\n\t 5) Salir\n-->\t");
        scanf("%d", &op);
        if(op==5) break;

        switch(op){
            case 1:
                generar(ajustes, &pass, size);
                printf("\n\n__________ PASSWORD GENERADA CON EXITO ! _________________");
                printf("\n\tPassword generada: \n\t--> %s", pass);
                break;
            case 2:
                do{
                    printf("\nIntroduzca el nuevo tamanio de la password: \n-->");
                    scanf("%d", &size);
                }while(size<=0);
                pass = (char *) realloc(pass, size * 1 * sizeof(char));
                break;
            case 3:
                do{
                    system("CLS");
                    fflush(stdin);
                    printf("\n\n\t____________ AJUSTES DEL GENERADOR _____________");
                    printf("\n\t 1) Minusculas ");
                    printf((ajustes.min==1)? "ON" : "OFF");
                    printf("\n\t 2) Mayusculas ");
                    printf((ajustes.may==1)? "ON" : "OFF");
                    printf("\n\t 3) Numeros ");
                    printf((ajustes.nums==1)? "ON" : "OFF");
                    printf("\n\t 4) Simbolos ");
                    printf((ajustes.simb==1)? "ON" : "OFF");
                    printf("\n\t 5) Salir\n\t--> ");
                    aux = getchar();
                    if(ajustes.min == 0 && ajustes.may == 0 && ajustes.simb == 0 && ajustes.nums == 0 && aux=='5'){
                        aux = '0';
                        printf("\n\nERROR: No puedes dejar el menu con las opciones apagadas\n");
                        system("PAUSE");
                    }
                    switch(aux){
                    case '1':
                        ajustes.min = (ajustes.min==1)? 0 : 1;
                        break;
                    case '2':
                        ajustes.may = (ajustes.may==1)? 0 : 1;
                        break;
                    case '3':
                        ajustes.nums = (ajustes.nums==1)? 0 : 1;
                        break;
                    case '4':
                        ajustes.simb = (ajustes.simb==1)? 0 : 1;
                        break;
                    }
                }while(aux != '5');
                    break;
                case 4:
                    verSeguridad();
                    break;
                default:
                    break;
        }
        printf("\n\n");
        system("PAUSE");
        system("CLS");
    }while(op != 5);

    free(pass);

    return 0;
}

PASS crearPass(){
    PASS temp;
    temp.min = 0;
    temp.may = 0;
    temp.nums = 0;
    temp.simb = 0;
    return temp;
}

void generar(PASS ajustes, char **pass, int size){

    srand(time(NULL));
    LISTA nuevaConfig = listaRand(ajustes);

    int i;
    int posRand = 0;
    int letraRand = 0;

    for(i=0; i<size; i++){
        posRand = rand()% nuevaConfig.cant;
        switch(nuevaConfig.lista[posRand]){
            case 0: //Minuscula
                letraRand = (rand() % (122 - 97 + 1)) + 97;
                break;
            case 1: //Mayuscula
                letraRand = (rand() % (90 - 65 + 1)) + 65;
                break;
            case 2: //Numero
                letraRand = (rand() % (57 - 48 + 1)) + 48;
                break;
            case 3: //Simbolo
                letraRand = (rand() % (47 - 33 + 1)) + 33;
                break;
        }
        (*pass)[i] = letraRand;
    }
    for(i=0; i<nuevaConfig.cant; i++)
        free(nuevaConfig.lista+i);
    return;
}

LISTA listaRand(PASS ajustes){
    LISTA temp;
    temp.cant = 0;
    temp.lista = (int *) calloc(1, sizeof(int));
    if(ajustes.min == 1){
        temp.cant++;
        temp.lista = (int *) realloc(temp.lista, sizeof(int) * temp.cant);
        temp.lista[temp.cant-1] = 0;
    }
    if(ajustes.may == 1){
        temp.cant++;
        temp.lista = (int *) realloc(temp.lista, sizeof(int) * temp.cant);
        temp.lista[temp.cant-1] = 1;
    }
    if(ajustes.nums == 1){
        temp.cant++;
        temp.lista = (int *) realloc(temp.lista, sizeof(int) * temp.cant);
        temp.lista[temp.cant-1] = 2;
    }
    if(ajustes.simb == 1){
        temp.cant++;
        temp.lista = (int *) realloc(temp.lista, sizeof(int) * temp.cant);
        temp.lista[temp.cant-1] = 3;
    }
    return temp;
}

void verSeguridad(){
    char *localPass = (char *) calloc(32, sizeof(char));
    int security = 0;
    int i;
    int bandMin = 0;
    int bandMay = 0;
    int bandNums = 0;
    int bandSimb = 0;
    printf("\n\n_____________ VER SEGURIDAD DE UN PASSWORD _____________");
    printf("\n\n\tIntroduzca su password para ver el nivel de seguridad\n\t--> ");
    fflush(stdin);
    fgets(localPass, 32, stdin);
    localPass[(int)strlen(localPass) -1 ] = '\0';
    for(i=0; i<(int)strlen(localPass)-1; i++){
        if(localPass[i]>='!' && localPass[i]<='/' && bandSimb == 0){
            security += 50;
            bandSimb = 1;
        }
        if(localPass[i]>='A' && localPass[i]<='Z' && bandMay == 0){
            security += 20;
            bandMay = 1;
        }
        if(localPass[i]>='a' && localPass[i]<='z' && bandMin == 0){
            security += 15;
            bandMin = 1;
        }
        if(localPass[i]>='0' && localPass[i]<='9' && bandNums == 0){
            security += 15;
            bandNums = 1;
        }
    }
    if(security >= 95)
        printf("\n\tPassword %s DEMASIADA SEGURA", localPass);
    else if(security >= 50 && security < 95)
        printf("\n\tPassword %s RELATIVAMENTE SEGURA", localPass);
    else if(security >= 30 && security < 50)
        printf("\n\tPassword %s INSEGURA", localPass);
    else
        printf("\n\tPassword %s MUY INSEGURA", localPass);
    free(localPass);
}
