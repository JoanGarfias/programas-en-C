#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = (int *) calloc(1, sizeof(int));
    int op;
    FILE *fp = fopen("test.txt", "r+"); // abrimos el archivo en modo lectura-escritura
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    if (fscanf(fp, "%p", (void**) &a) == 1) { // intentamos leer la dirección de memoria del archivo
        printf("La direccion de memoria en el archivo es: %p\n", (void *)a);
        printf("Contenido: %d\n", *a);
        printf("Desea borrar el contenido? (1 para si, 0 para no) --> ");
        scanf("%d",&op);
        if(op == 1){
            a = NULL;
            fclose(fp);
            fp = fopen("test.txt", "w"); // abrimos el archivo en modo escritura (lo vaciamos)
            fclose(fp);
        }
    }
    else { // si el archivo está vacío
        printf("Generando nuevo dato...\n");
        *a = 5;
        fprintf(fp, "%p", (void *)a); // escribimos la dirección de memoria del puntero en el archivo
    }
    fclose(fp);
    return 0;
}
