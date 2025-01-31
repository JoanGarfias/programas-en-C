#include <stdio.h>

int main(){
	int v1 = 3;
	int v2 = 5;
	
	int *ptr1, *ptr2;
	
	ptr1 = &v1;
	ptr2 = &v2;
	
	printf("\nv1: %p -> %d : %d", ptr1, *ptr1, v1);
	printf("\nv2: %p -> %d : %d", ptr2, *ptr2, v2);
	
	ptr1 = &v2;
	printf("\nIntercambio ptr1-v2: %p -> %d : %d", ptr1, *ptr1, v2);
	
	*ptr1 = 10;
	printf("\nNuevo contenido v2: %p -> %d : %d", ptr1, *ptr1, v2);
	
	return 0;
}