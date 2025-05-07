#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct control{
    int *elems;
    int size;
}CONTROL;

int string_is_number(char *);
int calc_r(int);
int upp(int, int);
int *string_to_int_array(char *, int);
int is_in_int_array(int, int *, int);

int main(int argc, char *argv[]){
    int i,j;
    if(argc != 3){
        perror("Usa los argumentos: ./hamming <encode/decode> <valor>");
        return 0;
    }
    if( ! string_is_number(argv[2])){
        perror("Usa los argumentos: ./hamming <encode/decode> <valor_binario>");
        return 0;
    }

    if(strcmp(argv[1], "encode") == 0){
        //Conseguimos el tamaño del mensaje
        int message_len = strlen(argv[2]);
        int cont_message_init = 0;

        //Los convertimos a un array de enteros
        int *message = string_to_int_array(argv[2], message_len);
        printf("\nMensaje recibido: %s", argv[2]);

        printf("\nEl mensaje recibido en array int es: ");
        for(i=0; i < message_len; i++){
            printf("%d", message[i]);
        }
        printf("\n:)\n");


        //Intentamos calcular "r"
        int r = calc_r(message_len);
        int *r_items = (int *) calloc(r, sizeof(r)); //Conjunto de posiciones para bits de paridad
        for(i=0; i < r; i++){
            r_items[i] = upp(2,i);
        }

        //Calculamos el tamaño del mensaje ya codificado
        int message_code_size = message_len + r;

        int *message_code = (int *) calloc(message_code_size, sizeof(int));
        //Primero copiamos todo el mensaje inicial al mensaje codificado
        for(i=0; i < message_code_size; i++){
            if(!is_in_int_array(i, r_items, r)){ //Es un bit de paridad
                message_code[i] = message[cont_message_init];
                cont_message_init++;
            }
        }

        //Luego calcularemos los bits de paridad
        int first_time_xor = 1;
        for(i=0; i < message_code_size; i++){
            if(is_in_int_array(i, r_items, r)){ //Es un bit de paridad
                for(j = 0; j < message_code_size; j++){
                    if( ! is_in_int_array(j, r_items, r)){ //Es un bit de paridad
                        continue;
                    }
                    else{
                        //di es el calculo de un XOR entre la posicion de un bit de paridad y un elemento del mensaje
                        //En este caso, i es la posición del bit de paridad, j es la posición de un elemento del mensaje
                        int di = i ^ j;
                        if(di == i){ //Si es una posicion controlada por un bit de paridad...
                            if(first_time_xor){
                                message_code[i] = message_code[j];
                                first_time_xor = 0;
                            }
                            else{
                                message_code[i] ^= message_code[j];
                            }
                        }
                    }
                }
            }
            first_time_xor = 1;
        }

        printf("\nEl mensaje codificado es: ");
        for(i=0; i < message_code_size; i++){
            printf("%d", message_code[i]);
        }
        printf("\n:)\n");
    }
    else if(strcmp(argv[1], "decode") == 0){

    }
    else{
        perror("Opcion no valida, usa los argumentos ./hamming <encode/decode> <valor>");
    }
    return 0;
}

int string_is_number(char *c){
    int i;
    for(i=0; i<strlen(c); i++){
        if(!isdigit(c[i]))
            return 0;
    }
    return 1;
}

int calc_r(int m){
    int r = 0;
    do{
        r++;
    }while(upp(2, r) < m + r + 1);
    return r;
}

int upp(int a, int b){
    int i;
    int acum = 1;
    for(i=1; i < b; i++){
        acum *= i;
    }
    return acum;
}

int *string_to_int_array(char *str, int str_len){
    int i;
    int *num = (int *) calloc(str_len, sizeof(int));
    printf("\nCadena recibida: %s\n", str);

    for(i=0; i < str_len; i++){
        num[i] = str[i] - '0';
    }
    return num;
}


int is_in_int_array(int value, int *array, int array_size){
    int i;
    for(i=0; i < array_size; i++){
        if(array[i] == value)
            return 1;
    }
    return 0;
}
