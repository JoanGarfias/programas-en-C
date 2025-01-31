#include <stdio.h>

int main() {
    FILE *archivo;
    int matriz[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    archivo = fopen("fpBinario.bin", "wb+");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return 1;
    }
    /*Normalmente, fwrite() se usa para escribir en un archivo 
	de tipo binario, este programa escribe una matriz en un archivo y posteriormente
	borra toda la matriz igualandola a cero, luego con fread() se vuelve a leer.*/
    fwrite(matriz, sizeof(int), 6, archivo);
	int i,j;
	for(i=0; i<2; i++){
		for(j=0; j<3; j++){
			matriz[i][j] = 0;
		}
	}
	rewind(archivo);
	
    fread(matriz, sizeof(int), 6, archivo);
    
	for(i=0; i<2; i++){
		for(j=0; j<3; j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
    
    fclose(archivo);
    
    return 0;
}
