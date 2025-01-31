#include <stdio.h>
#include <string.h>
#define TMC 64

int main(){
	char ruta[TMC];
	char texto[TMC];
	int i;
	printf("\nIntroduzca el nombre del archivo: \n---> ");
	scanf("%s",ruta);
	strcat(ruta,".txt");
	FILE *fp = fopen(ruta, "r");
	size_t contChars = fread(texto, 1, TMC, fp);
	
	//fread devuelve la cantidad de caracteres que se pudieron leer

	printf("\nSe leyeron %ld caracteres en el archivo %s\n------\n",contChars, ruta);
	for(i=0; i<contChars; i++){
		printf("POS[%d] -> %c\n",i,texto[i]);
	}

	fclose(fp);
}
