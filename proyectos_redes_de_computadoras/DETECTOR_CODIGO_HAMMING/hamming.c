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
        printf("\nEl valor de (r) es: %d", r);
        int *r_items = (int *) calloc(r, sizeof(r)); //Conjunto de posiciones para bits de paridad
        printf("\nConjunto de posiciones para bits de paridad: \n");

        for(i=0; i < r; i++){
            r_items[i] = upp(2,i);
            printf("2 ^ %d = %d\n", i, upp(2,i));
            printf("%d ", r_items[i]);
        }

        //Calculamos el tamaño del mensaje ya codificado
        int message_code_size = message_len + r;

        int *message_code = (int *) calloc(message_code_size, sizeof(int));
        //Primero copiamos todo el mensaje inicial al mensaje codificado
        for(i=0; i < message_code_size; i++){
            if(!is_in_int_array(i+1, r_items, r)){ //Es un bit de paridad
                message_code[i] = message[cont_message_init];
                printf("\nColoque un bit de mensaje [%d] en la posición [%d]", message_code[i], i+1);
                cont_message_init++;
            }
        }

        //Luego calcularemos los bits de paridad
        int first_time_xor = 1;

        for(i=0; i < message_code_size; i++){
            if(is_in_int_array(i+1, r_items, r)){ //Es un bit de paridad
                printf("\nHola");
                for(j = 0; j < message_code_size; j++){
                    //di es el calculo de un XOR entre la posicion de un bit de paridad y un elemento del mensaje
                    //En este caso, i es la posición del bit de paridad, j es la posición de un elemento del mensaje
                    if(j == i) continue;
                    printf("pepe\n");

                    int di = 0;
                    int i_aux = i;
                    int j_aux = j;
                    di = (i_aux+1) & (j_aux+1);
                    if(di != 0){ //Si es una posicion controlada por un bit de paridad...
                        if(first_time_xor){
                            message_code[i] = message_code[j];
                            first_time_xor = 0;
                            printf("\nEs el primer xor, asi que lo de abajo no vale");
                        }
                        else{
                            message_code[i] ^= message_code[j];
                        }
                        printf("\nAplicaré un XOR entre las posiciones [%d] y [%d], o sea los valores (%d) y (%d)",
                            i+1, j+1, message_code[i], message_code[j]);
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
        printf("\nEl valor de (r) es: %d", r);
        int *r_items = (int *) calloc(r, sizeof(r)); //Conjunto de posiciones para bits de paridad
        printf("\nConjunto de posiciones para bits de paridad: \n");

        for(i=0; i < r; i++){
            r_items[i] = upp(2,i);
            printf("2 ^ %d = %d\n", i, upp(2,i));
            printf("%d ", r_items[i]);
        }

        //Calculamos el tamaño del mensaje ya codificado

        int *message_code = (int *) calloc(message_len, sizeof(int));
        int *message_sec = (int *) calloc(r, sizeof(int));

        //Primero copiamos todo el mensaje inicial al mensaje codificado
        for(i=0; i < message_len; i++){
            message_code[i] = message[cont_message_init];
            printf("\nColoque un bit de mensaje [%d] en la posición [%d]", message_code[i], i+1);
            cont_message_init++;
        }

        //Luego calcularemos los bits de paridad
        int first_time_xor = 1;
        int cont_message_sec = 0;

        for(i=0; i < message_len; i++){
            if(is_in_int_array(i+1, r_items, r)){ //Es un bit de paridad
                for(j = 0; j < message_len; j++){
                    //di es el calculo de un XOR entre la posicion de un bit de paridad y un elemento del mensaje
                    //En este caso, i es la posición del bit de paridad, j es la posición de un elemento del mensaje
                    if(j == i) continue;

                    int di = 0;
                    int i_aux = i;
                    int j_aux = j;
                    di = (i_aux+1) & (j_aux+1);
                    if(di != 0){ //Si es una posicion controlada por un bit de paridad...
                        if(first_time_xor){
                            message_sec[cont_message_sec] = message_code[j];
                            first_time_xor = 0;
                            printf("\nEs el primer xor, asi que lo de abajo no vale");
                        }
                        else{
                            message_sec[cont_message_sec] ^= message_code[j];
                        }
                        printf("\nAplicaré un XOR entre las posiciones [%d] y [%d], o sea los valores (%d) y (%d)",
                            i+1, j+1, message_code[i], message_code[j]);
                    }
                }
                cont_message_sec++;
            }
            first_time_xor = 1;
        }

        printf("\nContador de bits de paridad: %d\n", cont_message_sec);
        for(i=0; i < cont_message_sec; i++){
            printf("%d ", message_sec[i]);
        }
        printf("\n");

        cont_message_sec = 0;
        int error_pos = -1;
        for(i=0; i < message_len; i++){
            if(is_in_int_array(i+1, r_items, r)){ //Si es un bit de paridad
                if(message_sec[cont_message_sec] != message_code[i]){
                    printf("\nEncontre que el bit en el mensaje en la posicion [%d] no coincide\n", i);
                    if(error_pos == -1){ //Primera suma
                        error_pos = i+1;
                        printf("Primera vez el error vale %d ", error_pos);
                    }
                    else{
                        error_pos += (i+1);
                    }
                }
                cont_message_sec++;
            }
        }

        printf("\nEl mensaje codificado es: ");
        for(i=0; i < message_len; i++){
            printf("%d", message_code[i]);
        }

        if(error_pos != -1){ //Hay error
            printf("\nHay un error en la posición [%d]", error_pos);
            printf("\nEl mensaje corregido es: ");
            message_code[error_pos-1] = !message_code[error_pos-1];
            for(i=0; i < message_len; i++){
                printf("%d", message_code[i]);
            }
        }
        else{
            printf("\nNo hay error detectado");
        }

        printf("\n:)\n");
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
    for(i=1; i <= b; i++){
        acum *= a;
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
