#include<stdio.h>

#define TMC 64

int main(){
	char texto[TMC];
	char temp;
	fpos_t pos;
	
	FILE *fp = fopen("FEOF_FGETPOS.txt", "r");
	
	fgets(texto, TMC, fp);
	puts(texto);
	
	rewind(fp); //regresar a la primera posicion
	printf("------\nUsando funciones FEOF y FGETPOS");
	while(!feof(fp)){
		temp = getc(fp);
		fgetpos(fp, &pos);
		printf("\nLa posicion de %c en el archivo es: %ld",temp, pos);
	}
	printf("\nEl archivo llego a su fin");
	
	fclose(fp);
	return 0;
}