#include <stdio.h>
#include <stdarg.h>

long int sumar(int, ...);

int main(){
	
	int test = sumar(5, 1, 2, 3 ,4 ,5);
	printf("%d",test);
	return 0;
}

long int sumar(int counter, ...){
	va_list args;
	va_start(args,counter);
	int i;
	long int suma=0;
	for(i=0; i<counter; i++){
		suma += va_arg(args, int);
	}
	va_end(args);
	return suma;
}