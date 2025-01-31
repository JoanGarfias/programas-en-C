#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define N_CIF 15

char texto[64];
void mostrarInicio(int *);
void pedirDatos(int *op, char texto[64]);
void cifrarTexto(char texto[64]);
void descifrarTexto(char texto2[64]);

char abc[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'				
};

int main(){	system("cls");
	int op=0;
	mostrarInicio(&op);
	pedirDatos(&op,texto);
	if(op==1)
		cifrarTexto(texto);
	else
		descifrarTexto(texto);
	return 0;	
}

void cifrarTexto(char texto[64]){
	int i,j; int aux;
	if(N_CIF<51 && N_CIF!=1)
		aux=51%N_CIF;
	else
		aux=N_CIF%51;
	char texto2[strlen(texto)+1];
	if(N_CIF>0) //validamos el desplazamiento
	{
		for(i=0; i<strlen(texto); i++){
			for(j=0; j<strlen(abc); j++){
				if(texto[i] == abc[j]){ //busqueda de carácter
					if(j+aux > 51){
						texto2[i] = abc[aux-(51-j)];
						break;
					}
					texto2[i] = abc[j+aux]; //por defecto, si no hay problemas con el rango, sumamos la diferencia
					break;
				}
				else{
					texto2[i] = texto[i];
					continue;
				}
			}
		}
		texto2[strlen(texto)] = '\0';
		system("color 2f");
		printf("\n\n\tSU TEXTO: \t");	puts(texto);
		printf("\n\tHA SIDO CIFRADO A: \t");	puts(texto2);
		system("PAUSE");
		main();
	}
	else{
		exit(-1);
	}
}


void descifrarTexto(char texto2[64])
{
	int i,j,aux;
	if(N_CIF<51 && N_CIF!=1)
		aux=51%N_CIF;
	else
		aux=N_CIF%51;
	char texto3[strlen(texto2) +1];
	if(N_CIF>0)
	{
		for(i=0; i<strlen(texto2)+1; i++){ //letra por letra del texto ingresado por el usuario
			for(j=0; j<strlen(abc); j++){  //letra por letra del abecedario
				if(texto2[i] == abc[j]){
					if(j-aux < 0){
						texto3[i] = abc[(j+51)-aux];
						break;
					}
					texto3[i] = abc[j-aux];
					break;
				}
				else{
					texto3[i] = texto2[i];
				}
			}
		}
		texto3[strlen(texto2)] = '\0';
		system("color 2f");
		printf("\n\n\tSU TEXTO: \t");	puts(texto2);
		printf("\n\tDESCIFRADO ES: \t");	puts(texto3);
		system("PAUSE");
		main();
	}
	else{
		exit(-1);
	}
}


void mostrarInicio(int *op)
{
	system("color 9f");
	do{
		printf("\n\n\t\tSISTEMA DE CIFRADO/DESCIFRADO\n\n\n\tMENU DE SELECCION");
		printf("\n\n\n\t1.- CIFRADO\n\n\t2.- DESCIFRADO\n\n\tSELECCION: \t");
		scanf("%d",op);
		system("cls");
		if(*op>2 || *op<1){
			printf("\n\n\tERROR: Introduzca una opcion valida");
			system("color 4f");
		}
	}while(*op>2 || *op<1);
}


void pedirDatos(int *op, char texto[64])
{
	system("color 20");
	do{
		system("cls");
		if(*op==1){
			system("cls");
			printf("\n\n\tEscogio la opcion CIFRADO DE TEXTO");
			printf("\n\n\tIntroduzca el texto a CIFRAR: \n\t---->>>  ");
			fflush(stdin);
			gets(texto);
		}
		else{
			printf("\n\n\tEscogio la opcion DESCIFRADO DE TEXTO");
			printf("\n\tIntroduzca el texto a DESCIFRAR: \n\t---->>>  ");
			fflush(stdin);
			gets(texto);
		}
		if (texto[0]=='\0' || (int) isdigit(texto[0]) || texto[0]=='-'){
			printf("\nERROR: Introduzca un texto valida, debe iniciar con una letra.\n");
			system("color 4f");
			system("PAUSE");
		}
	}while(texto[0]=='\0' || (int) isdigit(texto[0]) || texto[0]=='-');
}