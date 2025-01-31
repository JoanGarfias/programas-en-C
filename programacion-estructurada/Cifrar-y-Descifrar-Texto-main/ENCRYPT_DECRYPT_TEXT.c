//A program that can encrypt or decrypt text entered by the user

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define N_CIF 130 /*this is the constant of motion in the position of the alphabet*/

char text[64];
void showStartScreen(int *);
void requestData(int *option, char text[64]);
void encryptText(char text[64]);
void decryptText(char text2[64]);

char abc[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'				
};

int main(){	system("cls");
	int option=0;
	showStartScreen(&option);
	requestData(&option,text);
	(option==1)?	encryptText(text): decryptText(text);
	return 0;	
}

void encryptText(char text[64]){
	int i,j; int aux;
	
	aux = (N_CIF<51 && N_CIF!=1)? 	51%N_CIF : N_CIF%51; /*Calculate the real number of motion in the position ABC*/

	char text2[strlen(text)+1];

	if(N_CIF>0) //An motion valid (more than 0)
	{
		for(i=0; i<strlen(text); i++){
			for(j=0; j<strlen(abc); j++){
				if(text[i] == abc[j]){ //The search of char
					if(j+aux > 51){
						text2[i] = abc[aux-(51-j)];
						break;
					}
					text2[i] = abc[j+aux]; //if the range is not outside range, we'll add the difference
					break;
				}
				else{
					text2[i] = text[i];
					continue;
				}
			}
		}
		text2[strlen(text)] = '\0'; //add the '\0' char to array.
		system("color 2f");
		printf("\n\n\tText input: \t");	puts(text);
		printf("\n\fENCRYPT: \t");	puts(text2);
		system("PAUSE");
		main();
	}
	else{ //exception with N_CIF (N_CIF less than 0 or equals 0)
		exit(-1);
	}
}


void decryptText(char text2[64])
{
	int i,j,aux;
	aux = (N_CIF<51 && N_CIF!=1)?	51%N_CIF : N_CIF%51;
	char text3[strlen(text2) +1];
	if(N_CIF>0)
	{
		for(i=0; i<strlen(text2)+1; i++){ //Search of letter by letter.
			for(j=0; j<strlen(abc); j++){  //Search of letter by ABC.
				if(text2[i] == abc[j]){
					if(j-aux < 0){
						text3[i] = abc[(j+51)-aux];
						break;
					}
					text3[i] = abc[j-aux];
					break;
				}
				else{
					text3[i] = text2[i];
				}
			}
		}
		text3[strlen(text2)] = '\0';
		system("color 2f");
		printf("\n\n\tText input: \t");	puts(text2);
		printf("\n\tDECRYPT: \t");	puts(text3);
		system("PAUSE");
		main();
	}
	else{ //exception with N_CIF (N_CIF less than 0 or equals 0)
		exit(-1);
	}
}


void showStartScreen(int *option)
{
	system("color 9f");
	do{
		printf("\n\n\t\tPROGRAM ENCRYPT/DECRYPT\n\n\n\tOPTIONS:");
		printf("\n\n\n\t1.- ENCRYPT TEXT\n\n\t2.- DECRYPT TEXT\n\n\tSELECTION: \t");
		scanf("%d",option);
		system("cls");
		if(*option>2 || *option<1){
			printf("\n\n\tERROR: The option is not valid");
			system("color 4f");
		}
	}while(*option>2 || *option<1);
}


void requestData(int *option, char text[64])
{
	system("color 20");
	do{
		system("cls");
		if(*option==1){
			system("cls");
			printf("\n\n\tThe option is ENCRYPT TEXT");
			printf("\n\n\tPlease, enter the text to be encrypted: \n\t---->>>  ");
			fflush(stdin);
			gets(text);
		}
		else{
			system("cls");
			printf("\n\n\tThe option is DECRYPT TEXT");
			printf("\n\n\tPlease, enter the text to be decrypted: \n\t---->>>  ");
			fflush(stdin);
			gets(text);
		}
		if (text[0]=='\0' || (int) isdigit(text[0]) || text[0]=='-'){
			printf("\nERROR: Please, enter a text valid, you must put a number 1 or 2.\n");
			system("color 4f");
			system("PAUSE");
		}
	}while(text[0]=='\0' || (int) isdigit(text[0]) || text[0]=='-');
}
