#include <stdio.h>
#include <string.h>

int main(){
	char textoRecibido[256];
	char palabraBuscada[] = "hola";
	FILE *fp = fopen("test.txt","r");
	int apariciones = 0;
	while(fscanf(fp, "%s", textoRecibido) != EOF){
		if(strcmp(palabraBuscada, textoRecibido) == 0){
			apariciones++;
		}
	}
	printf("\nAparece %d veces",apariciones);
	
	fclose(fp);
	
	return 0;
}