//Program that can check if N numbers entered by the user are even or odd, prime and palindrome.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int counterDigs(int);
int capicuousNumber(int);
int evenNumber(int);
int primeNumber(int);

int main(){
	int counter=1,i;
	int number;
	int *Numbers = NULL; /*a NULL pointer -> Dynamic Memory*/
	printf("\nWelcome!, if you want to exit in Program, press 0");
	do{
		do{
			printf("\nGive a positive number: \t");
			scanf("%d",&number);
		}while(number<0); /*The validation of range numbers*/
		if (number==0) break; /*If the number is 0, exit*/
		Numbers = (int *) realloc ((void *)Numbers, sizeof(int)*counter); /*depends on the number counter*/
		*(Numbers+counter-1) = number;
		counter++;
	}while(number!=0);
	
	for(i=0; i<counter-1; i++){ /*Call functions evenNumber,primeNumber,etc*/
		printf("\n%d is ",*(Numbers+i));
			if(evenNumber(*(Numbers+i)))
				printf("even");
			else
				printf("odd");
			if(primeNumber(*(Numbers+i)))
				printf(" prime");
			if(*(Numbers+i) > 10){
				if(capicuousNumber(*(Numbers+i)))
					printf(" capicuous");
			}
	}
	free(Numbers);
}

int primeNumber(int number){
	int i,div=0;
	for(i=2; i<=number/2; i++){ /*Default, the number has two dividers*/
		if (number%i==0) div++;
	}
	return (div==0 && number!=1)? 1:0;
}

int evenNumber(int number){
	return !(number%2);
}

int capicuousNumber(int num){
	int num_aux=num,i=0;
	int digs = counterDigs(num);
	int *Numbers_cap = NULL;
	int n1=0,n2=0;
	Numbers_cap = (int *) realloc ((void *) Numbers_cap, sizeof(int)*digs);
	for(i=0; i<digs; i++){
		num_aux = num%10; /*Save the number of Unit*/
		*(Numbers_cap+i) = num_aux; /*Save the every Unity in a Numbers_cap pointer*/
		 num = num/10;
	}
	for(i=0; i<digs; i++){
		n1 = n1 + *(Numbers_cap+i) * pow(10,i); /*Transformation of */
		n2 = n2 + *(Numbers_cap+digs-i-1) * pow(10,i);
	}
	free(Numbers_cap);
	return (n1==n2)? 1:0;
}

int counterDigs(int number){
	int digs=0;
	while(number!=0){
		number = number/10;
		digs++;
	}
	return digs;
}
