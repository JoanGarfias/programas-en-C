#include <stdio.h>

int main(){
	char texto[] = "920.235 902.0 212.2";
	double a,b,c;
	sscanf(texto,"%lf %lf %lf",&a,&b,&c); //Lee el formato de una cadena
	printf(" a: %lf \n b: %lf \n c: %lf",a,b,c);
	printf("\n\n------\n\nCadena: \n");
	puts(texto);
	
	return 0;
}