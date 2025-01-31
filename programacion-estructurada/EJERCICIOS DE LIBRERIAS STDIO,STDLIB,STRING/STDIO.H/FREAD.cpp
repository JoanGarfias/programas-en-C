#include<stdio.h>

#define TMC 64

int main(){
	char ruta[TMC];
	int i;
	printf("\nIntroduzca su ruta: \n---> ");
	scanf("%s",ruta);
	FILE *fp = fopen(ruta, "r");
	size_t contChars = fread(ruta, 1, TMC, fp);
	
	printf("\nSe leyeron %ld caracteres en el archivo %s\n------",contChars, ruta);
	for(i=0; i<contChars; i++){
	}
	
	fclose(fp);
}