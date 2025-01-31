#include <stdio.h>
#include <stdlib.h>

int main(){
	double *nums = NULL;
	char texto[] = "920.235 902.000 212.2 2.5 9.1";
	int i=0;
	int cont=0;
	int error=0;
	int contAux=0;
	char *p = texto;
	while(*p!='\0'){
		printf("%d:",i);
		nums = (double *) realloc(nums, sizeof(double) * (cont+1) );
		error = sscanf(p,"%lf%n",nums+cont,&i); //%n es la cantidad de caracteres avanzados
		if(error != 1) break; //sscanf devuelve 1 si se pudo realizar
		printf("%d\n",i);
		cont++;
		p += i;
		if(p[i]=='\0' && contAux==0){ //prevenir la ultimo lectura
			p[i]='0';
			contAux++;
		}
	}
	printf("\n\n");
	for(i=0; i<cont; i++){
		printf("%lf\n",nums[i]);
	}
}