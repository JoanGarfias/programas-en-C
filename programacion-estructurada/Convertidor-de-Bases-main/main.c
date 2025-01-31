//A PROGRAM THAT CAN CONVERT THE DECIMAL, OCTAL, HEXADECIMAL, BINARY BASE.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

char *base = NULL;
long int *base_n = NULL;
char hex[64];
long int number=0;

#include "basetools.h"
#include "convertbase.h"

/*Function main*/
int main(){
	base = (char *) malloc(sizeof(char));
	base_n = (long int *) malloc(sizeof(long int));
	int op=0,opExt=0;
	showOptionScreen(&op);
	switch(op){
		case 1: //DEC -> HEX,OCT,BIN
			showExtOpScreen(&opExt,1);
			requestNumber(1);
			switch(opExt){
				case 1:
					printf("\nThe number in Decimal Base (%ld) to Hexadecimal is:\n ->\t",number);
					puts(convertDecHex(number));
					break;
				case 2:
					printf("\nThe number in Decimal Base (%ld) to Octal is:\n ->\t",number);
					convertDecOctBin(number,1);
					break;
				case 3:
					printf("\nThe number in Decimal Base (%ld) to Binary is:\n ->\t",number);
					convertDecOctBin(number,2);
					break;
			}
			break;
		case 2:	//HEX -> DEC,OCT,BIN.
			showExtOpScreen(&opExt,2);
			requestNumber(2);
			switch(opExt){
				case 1: //HEX->DEC
					printf("\nThe number in Hexadecimal base (%s) to Decimal is: \n\t-> %ld",hex,convertHexDec(hex));
					break;
				case 2: //HEX->OCT
					printf("\nThe number in Hexadecimal base (%s) to Octal is: \n\t-> ",hex);
					convertHexOct(hex);
					break;
				case 3: //HEX->BIN
					printf("\nThe number in Hexadecimal base (%s) to Binary is: \n\t-> ",hex);
					convertHexBin(hex);
					break;
			}
			break;
		case 3:
			showExtOpScreen(&opExt,3);
			requestNumber(3);
			switch(opExt){
				case 1: //OCT -> DEC
					printf("\nThe number in Octal base (%ld) to Decimal is: \n->\t %ld",number,convertOctDec(number));
					break;
				case 2: //OCT -> HEX
					printf("\nThe number in Octal base (%ld) to Hexadecimal is: \n->\t",number);
					puts(convertOctHex(number));
					break;
				case 3: //OCT -> BIN
					printf("\nThe number in Octal base (%ld) to Binary is: \n->\t",number);
					convertOctBin(number);
					break;
			}
			break;
		case 4:
			showExtOpScreen(&opExt,4);
			requestNumber(4);
			switch(opExt){
				case 1: //BIN -> DEC
					printf("\nThe number in Binary base (%ld) to Decimal is: \n->\t %ld",number,convertBinDec(number));
					break;
				case 2: //BIN -> HEX
					printf("\nThe number in Binary base (%ld) to Hexadecimal is: \n->\t",number);
					puts(convertBinHex(number));
					break;
				case 3: //BIN -> OCT
					printf("\nThe number in Binary base (%ld) to Octal is: \n->\t",number);
					convertBinOct(number);
					break;
			}
			break;
		default:
			exit(0);
	}
	
	return 0;
}
