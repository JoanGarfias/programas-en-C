#include <stdio.h>
#include <stdarg.h>

long int sumaFactorial(int counter, ...);
long long int factorial(long int num);

int main(){
	long long int num = sumaFactorial(3, 5, 2, 3);
	printf("\n= %lld",num);
	
	return 0;
}

long int sumaFactorial(int counter, ...){
	va_list(args);
	va_start(args, counter);
	int i;
	char op = '+';
	long long int suma = 0;
	long int numTemp = 0;
	for(i=1; i<=counter; i++){
		numTemp = va_arg(args,long int);
 		printf("%ld!",numTemp);
		suma += factorial(numTemp);
		if(i!=counter)
			printf("%c",op);
	}
	return suma;
}

long long int factorial(long int num){
	if(num==1)
		return 1;
	return num * factorial(num-1);
}