#include <stdio.h>

int main() {
    FILE *archivo;
    char caracter;
    char texto[64] = "Hola soy joan";
    
    archivo = fopen("fgetc.txt", "r");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return 1;
    }
    
    // Leer y mostrar cada caracter del archivo
    while ((caracter = fgetc(archivo)) != EOF) {
        printf("%c", caracter);
    }
    
    //Regresa el puntero del archivo al inicio
    rewind(archivo);

	printf("\n\n");
	//Imprime la cadena texto en el archivo stdout
	fputs(texto, stdout);
    
    
    fclose(archivo);
    
    return 0;
}