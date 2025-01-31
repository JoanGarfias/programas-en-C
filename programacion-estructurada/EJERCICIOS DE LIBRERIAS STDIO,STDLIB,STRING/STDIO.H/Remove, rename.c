#include <stdio.h>

void pedirOpcion(int *);

int main(){
	int op=0;
	char path[64];
	char path2[64];
	do{
		pedirOpcion(&op);
		printf("\nIntroduzca el nombre del archivo con su extension\n--> ");
		scanf("%s",path);
		switch(op){
			case 1:
				printf("\nIntroduzca el nuevo nombre con su extension\n--> ");
				scanf("%s",path2);
				if(! (rename(path, path2) ) ){
					printf("\nEl nombre del archivo %s cambio a %s", path, path2);
				}
				else{
					printf("\nOcurrio un error al cambiar el nombre del archivo %s",path);
				}
				
				break;
			case 2:
				if(! remove(path) ){
					printf("\nEl archivo %s fue borrado con exito", path);
				}
				else{
					printf("\n(!) Ocurrio un error al intentar borrar su archivo %s",path);
				}
			break;
		}
	}while(op!=3);
	
	
	
	return 0;
}

void pedirOpcion(int *op){
	do{
		printf("\nOpcion 1: Renombrar archivo");
		printf("\nOpcion 2: Borrar archivo\n--> ");
		scanf("%d",op);
	}while(*op<1 || *op>3);
}