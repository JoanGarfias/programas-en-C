#include <stdio.h>

int main(){
	
	char texto[64];
	do{
		scanf("%s",&texto);
		if(!feof(stdin)){
			printf("\n%s",texto);
		}
	}while(!feof(stdin));
}