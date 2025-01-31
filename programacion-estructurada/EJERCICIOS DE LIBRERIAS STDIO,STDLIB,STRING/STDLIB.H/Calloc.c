#include <stdio.h>
#include <stdlib.h>

int main(){
	double *texto = calloc(10, sizeof(double));
	
	int i;
	for(i=0; i<10; i++){
		printf("%lf\n",*(texto+i) );
	}
	
	return 0;
} 