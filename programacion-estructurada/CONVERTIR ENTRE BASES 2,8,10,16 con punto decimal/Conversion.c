#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/*Constantes para saber la base escojida*/
#define ID_DEC 1
#define ID_HEX 2
#define ID_OCT 3
#define ID_BIN 4
#define ID_TODO 5

#define MAXBITS_BINCONV 5 /*Por defecto, si se ingresa base decimal tipo flotante
							, se mostraran esta cantidad de bits del numero*/

/*Funciones de Menu*/
int pedirOpcion();
int pedirBaseAConvertir(int);
void pedirCadena(const int, const int);
void limpiarCadena(); //Para el hexadecimal
double obtenerNumero();
int contarDigitos(double num);

/*Funciones de conversion*/
void convertirDEC(const int, const int, double);
void convertirHEX(const int);
void convertirOCT(const int);
void convertirBIN(const int);

char texto[64]; //Para binario y hexadecimal
char RHex[64]; //Resultados en hexadecimal
int contDigsN1 = 0; /*Variables para contador de parte entera y fraccionaria*/
int contDigsN2 = 0;

int main(){
	int base = 0;
	int conversion = 0;
	double num = 0;
	do{
		base = pedirOpcion();
		if(base==5)	break;
		conversion = pedirBaseAConvertir(base);
		switch(base){
			case 1:
				pedirCadena(ID_DEC, conversion);
				convertirDEC(conversion, -1, 0);
				break;
			case 2:
				pedirCadena(ID_HEX, conversion);
				convertirHEX(conversion);
				break;
			case 3:
				pedirCadena(ID_OCT, conversion);
				convertirOCT(conversion);
				break;
			case 4:
				pedirCadena(ID_BIN, conversion);
				convertirBIN(conversion);
				break;
			case 5:
				exit(0);
		}
		printf("\n\n");
		system("PAUSE");
		system("cls");
	}while(base!=5);
	
	return 0;
}

int pedirOpcion(){
	int op;
	do{
		printf("\n____________________________________________");
		printf("\n\n         [ Programa de Conversion ]");
		printf("\n____________________________________________");
		printf("\n\n\tEscoja su base: ");
		printf("\n\t1.- DECIMAL \t2.- HEXADECIMAL");
		printf("\n\t3.- OCTAL \t4.- BINARIO \n\t5.- Salir \n\n\t-->   ");
		scanf("%d",&op);
		if(op<1 || op>5){
			printf("\nERROR: Introduzca una opcion valida\n");
			system("PAUSE");
			system("cls");
		}
	}while(op<0 || op>5);
	return op;
}

int pedirBaseAConvertir(int base){
	int conversion = ID_TODO;
	system("cls");
	char baseTexto[32];
	strcpy(baseTexto, (base==ID_DEC)? "DECIMAL" : (base==ID_HEX)? "HEXADECIMAL" :
						(base==ID_OCT)? "OCTAL" : "BINARIO");
	do{
		printf("\n____________________________________________");
		printf("\n\n         [ Escojer base a convertir ]");
		printf("\n____________________________________________");
		printf("\n\n\tEscoja su base: ");
		printf("(!) Ya no puedes escojer %s",baseTexto);
		printf("\n\t1.- DECIMAL \t2.- HEXADECIMAL");
		printf("\n\t3.- OCTAL \t4.- BINARIO \n\t5.- TODAS \n\n\t-->   ");
		scanf("%d",&conversion);
		if(conversion < ID_DEC || conversion > ID_TODO || conversion==base){
			printf("\nERROR: No puedes escojer %s\n", baseTexto);
			system("PAUSE");
			system("cls");
		}
	}while(conversion < ID_DEC || conversion > ID_TODO || conversion==base);
}

void pedirCadena(const int base, const int conversion){
	int i,j, campoValido=1, contPunto = 0;
	char baseTexto[12]; /*Se excluyen los casos de decimal, octal, esos ocupan numeros*/
	char conversionTexto[12];
	contDigsN1 = 0;
	contDigsN2 = 0;
	strcpy(baseTexto, (base==ID_DEC)? "DECIMAL" : (base==ID_HEX)? "HEXADECIMAL" :
						(base==ID_OCT)? "OCTAL" : "BINARIO" );
	strcpy(conversionTexto, (conversion==ID_DEC)? "DECIMAL" : (conversion==ID_HEX)? "HEXADECIMAL" :
						(conversion==ID_OCT)? "OCTAL" : (conversion==ID_BIN)? "BINARIO" : "TODOS");
	system("cls");

	if(base==ID_DEC){
		do{
			printf("Testestst");
			campoValido = 1;
			printf("\n____________________________________________");
			printf("\n\n         [ De %s a %s ]", baseTexto, conversionTexto);
			printf("\n____________________________________________");
			printf("\n\n\tIntroduzca el numero en base %s: \n--> ",baseTexto);
			fflush(stdin);
			gets(texto);
			if(texto[0]=='\0' || texto[0]=='.' || texto[strlen(texto)-1]=='.')
				campoValido = 0;
			for(i=0; i<(int)strlen(texto); i++){
				if(texto[i] == '.'){ //verificar la cantidad de puntos
					contDigsN1 = i;
					contPunto++; //Solo debe valer uno
					if(contPunto>1){
						campoValido = 0;
						break;
					}
				}
				else{
					if(isalpha(texto[i]) || !isdigit(texto[i]) ){
						campoValido=0;
						break;
					}
				}
			}
			if(!campoValido){
				printf("\nERROR: Tu numero no es valido\n\n");
				system("PAUSE");
				system("cls");
				contDigsN1 = 0;
				contPunto=0;
				limpiarCadena();
			}
		}while(!campoValido);
	}

	if(base==ID_OCT){
		do{
			campoValido = 1;
			printf("\n____________________________________________");
			printf("\n\n         [ De %s a %s ]", baseTexto, conversionTexto);
			printf("\n____________________________________________");
			printf("\n\n\tIntroduzca el numero en base %s: \n--> ",baseTexto);
			fflush(stdin);
			gets(texto);
			if(texto[0]=='\0' || texto[0]=='.' || texto[strlen(texto)-1]=='.')
				campoValido = 0;
			for(i=0; i<(int)strlen(texto); i++){
				if(texto[i] == '.'){ //verificar la cantidad de puntos
					contDigsN1 = i;
					contPunto++; //Solo debe valer uno
					if(contPunto>1){
						campoValido=0;
						break;
					}
				}
				if(isalpha(texto[i]) || texto[i]>'7'){
					campoValido=0;
					break;
				}
			}
			if(!campoValido){
				printf("\nERROR: Tu numero no es valido\n\n");
				system("PAUSE");
				system("cls");
				contDigsN1 = 0;
				contPunto=0;
				limpiarCadena();
			}
		}while(!campoValido);
	}

	if(base==ID_BIN){
		do{
			campoValido = 1;
			printf("\n____________________________________________");
			printf("\n\n         [ De %s a %s ]", baseTexto, conversionTexto);
			printf("\n____________________________________________");
			printf("\n\n\tIntroduzca el numero en base %s: \n--> ",baseTexto);
			fflush(stdin);
			gets(texto);
			if(texto[0]=='\0' || texto[0]=='.' || texto[strlen(texto)-1]=='.')
				campoValido = 0;
			for(i=0; i<(int)strlen(texto); i++){
				if(texto[i]!='.'){ //verificar si se ingresaron numeros diferentes de 0 o 1 o si son letras
					if(isalpha(texto[i]) || (texto[i]!='1' && texto[i]!='0') ){
						campoValido=0;
						break;
					}
				}
				if(texto[i] == '.'){ //verificar la cantidad de puntos
					contDigsN1 = i;
					contPunto++; //Solo debe valer uno
					if(contPunto>1){
						campoValido=0;
						break;
					}
				}
			}
			if(!campoValido){
				printf("\nERROR: Tu numero no es valido\n\n");
				system("PAUSE");
				system("cls");
				contDigsN1 = 0;
				contPunto=0;
				limpiarCadena();
			}
		}while(!campoValido);
	}
	else if(base==ID_HEX){
		do{
			campoValido = 1;
			printf("\n____________________________________________");
			printf("\n\n         [ De %s a %s ]", baseTexto, conversionTexto);
			printf("\n____________________________________________");
			printf("\n\n\tIntroduzca el numero en base %s: \n--> ",baseTexto);
			fflush(stdin);
			gets(texto);
			if(texto[0]=='\0' || texto[0]=='.' || texto[strlen(texto)-1]=='.')
				campoValido=0;
			for(i=0; i<(int)strlen(texto); i++){
				if(texto[i]=='.'){
					contDigsN1 = i;
					contPunto++; //Solo debe valer uno
					if(contPunto>1){
						printf("X ");
						campoValido=0;
						break;
					}
				}
				else{
					if( !( (texto[i] >= 'A' && texto[i]<='F' ) || isdigit(texto[i]) ) ) {
						campoValido=0;
						break;
					}
					else{
						if(!isalpha(texto[i]) && !isdigit(texto[i])){
							campoValido=0;
							break;
						}
					}
				}
			}
			if(!campoValido){
				printf("\nERROR: Tu numero no es valido\n\n");
				system("PAUSE");
				system("cls");
				contDigsN1 = 0;
				contPunto=0;
				limpiarCadena();
			}
		}while(!campoValido);
	}
	
	if(contPunto==1){
		contDigsN2 = (int) strlen(texto) - contDigsN1 - 1;
	}
	else{
		contDigsN1 = (int) strlen(texto);
		contDigsN2 = 0;
	}
	
	
}

void limpiarCadena(){
	int i;
	for(i=0; i<(int)strlen(RHex); i++){
		RHex[i] = '\0';
	}
	for(i=0; i<(int)strlen(texto); i++){
		texto[i] = '\0';
	}
}


void convertirDEC(const int CONVERSION, const int BASE, double AUX){
	int residuo = 0, contDigs = 0, i=0;
	double numero = obtenerNumero();
	if(BASE == ID_OCT || BASE == ID_BIN || BASE == ID_HEX){
		numero = AUX;	
	}
	double numAux = numero;
	int digitos = contarDigitos(numero);
	double parteFracc = numero - (int) numero;
	long int parteEnt = (int) numero;
	int contDigsFracc=0;

	int resultado[64];
	
	if(CONVERSION == ID_BIN || CONVERSION == ID_TODO){
		while(parteEnt!=0){
			residuo = parteEnt % 2;
			resultado[contDigs] = residuo;
			parteEnt /= 2;
			contDigs++;
		}
		printf("\nEl numero en base Binario es: \t");
		for(i=contDigs-1; i>=0; i--){
			printf("%d",resultado[i]);
		}
		if(parteFracc!=0){

			do{
				if(parteFracc*2.0 >= 1.0){
					resultado[contDigs+contDigsFracc] = 1;
					parteFracc = parteFracc*2.0 - 1.0;
				}
				else{
					resultado[contDigs+contDigsFracc] = 0;
					parteFracc = parteFracc*2.0;
				}
				contDigsFracc++;
			}while(contDigsFracc<5 && parteFracc>0);
			printf(".");
			for(i=contDigs; i<contDigs+contDigsFracc; i++){
				printf("%d",resultado[i]);
			}
		}
		numero = numAux;
		contDigs=0;
		residuo=0;
		residuo = 0, contDigs = 0, i=0;
		numero = numAux;
		parteFracc = numero - (int) numero;
		parteEnt = (int) numero;
		contDigsFracc=0;
	}
	
	if(CONVERSION == ID_OCT || CONVERSION == ID_TODO){
		while(parteEnt>=1){
			residuo = parteEnt % 8;
			resultado[contDigs] = residuo;
			parteEnt /= 8;
			contDigs++;
		}
		printf("\nEl numero en base Octal es: \t");
		for(i=contDigs-1; i>=0; i--){
			printf("%d",resultado[i]);
		}
		if(parteFracc!=0){
			printf(".%.0lf",parteFracc*8);
		}
		numero = numAux;
		contDigs=0;
		residuo=0;
		residuo = 0, contDigs = 0, i=0;
		numero = numAux;
		parteFracc = numero - (int) numero;
		parteEnt = (int) numero;
		contDigsFracc=0;
	}
	
	if(CONVERSION == ID_HEX || CONVERSION == ID_TODO){
		while(parteEnt!=0){
			residuo = parteEnt % 16; //Residuo guarda el valor numerico del numero en hexadecimal (0->15)
			parteEnt /= 16;
			switch(residuo){ //is a letter or a number?
				case 10:	RHex[contDigs]='A';	break;
				case 11: 	RHex[contDigs]='B';	break;
				case 12: 	RHex[contDigs]='C';	break;
				case 13: 	RHex[contDigs]='D';	break;
				case 14: 	RHex[contDigs]='E';	break;
				case 15: 	RHex[contDigs]='F';	break;
				default:
					RHex[contDigs] = residuo + '0';
			}
			contDigs++;
		}
		printf("\nEl numero en base Hexadecimal es: \t");
		for(i=contDigs-1; i>=0; i--){
			printf("%c",RHex[i]);
		}
		if(parteFracc!=0){
			switch((int) (parteFracc*16.0) ){
				case 10:	RHex[contDigs]='A';	break;
				case 11: 	RHex[contDigs]='B';	break;
				case 12: 	RHex[contDigs]='C';	break;
				case 13: 	RHex[contDigs]='D';	break;
				case 14: 	RHex[contDigs]='E';	break;
				case 15: 	RHex[contDigs]='F';	break;
				default:
					RHex[contDigs] = (int)(parteFracc*16.0) + '0';
			}
			printf(".%c",RHex[contDigs]);
		}
		limpiarCadena();
	}
	
}

void convertirOCT(const int CONVERSION){
	int residuo=0, i=0;
	double ROct = 0;
	int potNeg = 1;
	
	for(i=0; i<strlen(texto); i++){
		if(texto[i]=='.') i++;
		if(i<contDigsN1){
			ROct += (texto[i]-'0') * (pow(8,contDigsN1-i-1));	
		}
		else{
			ROct += (texto[i]-'0') * 1.0 / pow(8,potNeg);
			potNeg++;
		}
	}
	
	if(CONVERSION==ID_DEC || CONVERSION==ID_TODO){
		printf("\nEl numero en base Decimal es: %lf", ROct);
	}
	
	if(CONVERSION==ID_HEX || CONVERSION==ID_TODO){
		convertirDEC(ID_HEX, ID_HEX, ROct);
	}
	
	if(CONVERSION==ID_BIN || CONVERSION==ID_TODO){
		convertirDEC(ID_BIN, ID_HEX, ROct);
	}
	
}

void convertirHEX(const int CONVERSION){
	int i=0,aux=0;
	double RHexNum=0.0;
	int potNeg=1;
	for(i=0; i<strlen(texto); i++){
		if(texto[i]=='.') i++;
		switch(texto[i]){
			case 'A': aux=10; break;
			case 'B': aux=11; break;
			case 'C': aux=12; break;
			case 'D': aux=13; break;
			case 'E': aux=14; break;
			case 'F': aux=15; break;
			default:
				aux = texto[i]-'0';
		}
		if(i<contDigsN1){
			RHexNum += aux * (pow(16,contDigsN1-i-1));	
		}
		else{
			RHexNum += aux * 1.0 / pow(16,potNeg);
			potNeg++;
		}
	}
	
	if(CONVERSION==ID_DEC || CONVERSION==ID_TODO){
		printf("El numero en base Decimal es: %lf", RHexNum);
	}

	if(CONVERSION==ID_OCT || CONVERSION==ID_TODO){
		convertirDEC(ID_OCT, ID_OCT, RHexNum);
	}
	
	if(CONVERSION==ID_BIN || CONVERSION==ID_TODO){
		convertirDEC(ID_BIN, ID_BIN, RHexNum);
	}
}

void convertirBIN(const int CONVERSION){
	int i, potNeg=1;
	double RBinDec = 0.0;
	for(i=0; i<contDigsN1; i++)
		RBinDec += (texto[i]-'0') * pow(2,contDigsN1-i-1);
	for(i=contDigsN1+1; i<(int)strlen(texto); i++){
		RBinDec += (texto[i]-'0') * (double )1 / pow(2,potNeg);
		potNeg++;
	}

	if(CONVERSION==ID_DEC || CONVERSION==ID_TODO){
		printf("El numero en base Decimal es: %lf", RBinDec);
	}
	
	if(CONVERSION==ID_OCT || CONVERSION==ID_TODO){
		convertirDEC(ID_OCT, ID_OCT, RBinDec);
	}
	if(CONVERSION==ID_HEX || CONVERSION==ID_TODO){
		convertirDEC(ID_HEX, ID_HEX, RBinDec);
	}
}

double pedirNumeroDecFlot(){
	double num=0.0;
	do{
		printf("\nIntroduce el numero: \n--> ");
		scanf("%lf",&num);
	}while(num<0.0);
	return num;
}

double obtenerNumero(){
	int i;
	int potNeg=1;
	double num = 0.0;
	for(i=0; i<contDigsN1; i++){
		num += (texto[i]-'0') * pow(10,contDigsN1-i-1) * 1.0;
	}
	for(i=contDigsN1+1; i<strlen(texto); i++){
		num += (texto[i]-'0') * (double )1 / pow(10,potNeg);
		potNeg++;
	}
	return num;
}

int contarDigitos(double num){
	int numTemp = (int) num;
	int i=0;
	while(numTemp!=0){
		i++;
		numTemp/=10;
	}
	return i;
}