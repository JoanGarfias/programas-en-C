#include <stdio.h>

int main(){
	
	int c;
	while(EOF != (c=getchar())){
		putchar(c);
	}
	
	return 0;
}