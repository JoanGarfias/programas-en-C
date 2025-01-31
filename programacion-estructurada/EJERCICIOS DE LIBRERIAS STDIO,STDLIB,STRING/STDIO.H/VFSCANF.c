#include <stdio.h>
#include <stdarg.h>

int leerNumeros(FILE *, char *, ...);

int main(void) {
  int num1, num2, num3;
  FILE *archivo = fopen("VFSCANF.txt", "r");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 1;
  }

  leerNumeros(archivo, "%d%d%d", &num1, &num2, &num3);
  printf("Leidos: %d %d %d\n", num1, num2, num3);

  fclose(archivo);
  return 0;
}

int leerNumeros(FILE *archivo, char *formato, ...){
	va_list argumentos;
	int leidos = 0;
	
	va_start(argumentos, formato);
	leidos = vfscanf(archivo, formato, argumentos);
	va_end(argumentos);

	return leidos;
}