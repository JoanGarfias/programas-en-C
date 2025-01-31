#include <stdio.h>
#include <string.h>

int main(){
	
	char texto[64] = "Hola soy joan jaja";
	char dest[64];
	strcpy(dest, texto);
	fputs(dest, stdout);

	return 0;
}