#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<conio.h>

#define TMC 64
/*Funciones para conversion*/
int campoValido(char bin[TMC]);
void binToDec(char bin[]);
void imprimir(double);

//Variables para contar y separar la parte entera y decimal
int contDigsN1 = 0, contDigsN2 = 0;

int main(){
	char bin[TMC];
	do{
		printf("\n\nIntroduce el numero en binario: \n\n -> ");
		gets(bin);
		if(!campoValido(bin)){
			printf("\n\nERROR: Numero no valido");
		}
	}while(	!campoValido(bin) );
	binToDec(bin);
	getch();
	return 0;
}

int campoValido(char bin[TMC]){
	unsigned int i,contPunto=0;
	
	if(bin[0]=='\0' || bin[0]=='.')	return 0;
	
	for(i=0; i < (int)strlen(bin); i++){
		if(bin[i]!='.'){
			if(isalpha(bin[i]) || (bin[i]!='1' && bin[i]!='0')){
				return 0;
			}
		}
		if(bin[i] == '.'){
			contDigsN1 = i; //Posicion actual del punto son los digitos de la parte entera
			contPunto++; //Solo debe valer uno
			if(contPunto!=1){
				return 0;
			}
		}
	}
	if(contPunto==1){
		contDigsN2 = (int) strlen(bin) - contDigsN1 - 1;
	}
	else{
		contDigsN1 = (int) strlen(bin);
		contDigsN2 = 0;
	}
	return 1;
}

void binToDec(char bin[TMC]){
	unsigned int i=0, potNeg=1;
	double RS=0.0;
	
	for(i=0; i<contDigsN1; i++)
		RS += (bin[i]-'0') * pow(2,contDigsN1-i-1);

	for(i=contDigsN1+1; i<(int)strlen(bin); i++){
		RS += (bin[i]-'0') * (double )1 / pow(2,potNeg);
		potNeg++;
	}
	imprimir(RS);
}
void imprimir(double dec){
	int temp = (int) dec;
	printf("\nLa conversion a decimal es -> ");
	printf((dec-temp==0)? "%.0lf" : "lf",dec);
}