#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: encriptar <archivo> <clave>\n", argv[0]);
        return 1;
    }

    char *archivo = argv[1];
    char *clave = argv[2];

    printf("Archivo: %s\n", archivo);
    printf("Clave: %s\n", clave);

    return 0;
}
