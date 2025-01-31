#include <stdio.h>

int main(){
	FILE *fp = fopen("GETCHAR.txt","w+");
	char aux;
	while((aux = getchar() ) != '\n'){
		fputc(aux, fp);
	}

	fclose(fp);
	return 0;
}