#include <string.h>
#include <stdio.h>

int main(){ //convierte a minuscula un string
	char text[64];
	printf("\nString: \n-->  ");
	fgets(text, 64, stdin);
	strlwr(text);
	printf("%s",text);
	
	return 0;
}