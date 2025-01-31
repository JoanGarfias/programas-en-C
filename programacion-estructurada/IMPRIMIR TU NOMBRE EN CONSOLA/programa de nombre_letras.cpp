#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include "nombres.h"

void detectarLetra(char letra);
void imprimirLetra(char letra_nom[9][9]);
void pintarPantalla(int num);
char nombre[16];
int cont_let=0,tam=0;
//Letras son variables globales

int main(){
	int i,j;
	int espacios = 0;
	char letra;
	srand (time(NULL));
	
	printf("\nIntroduzca su nombre: \t");
	gets(nombre);
	tam = strlen(nombre);
	system("cls");
	for(i=0; i<tam; i++){
		if(nombre[i]==' '){
			tam--;
			espacios++;
		}
	}
	for(i=0; i<tam+espacios; i++){
		if(nombre[i]==' '){
			continue;
		}
		letra = nombre[i];
		detectarLetra(letra);
	}

	system("color 0f");
	system("PAUSE");
	return 0;
}

void detectarLetra(char letra){
	int i;
	cont_let++;
	
	printf("TU NOMBRE ES: \t");
	puts(nombre);
	printf("(!) Estoy mostrandote la letra %c (%d/%d)",letra,cont_let,tam);
	printf("\n\n");	
	if(letra=='A' or letra=='a')	imprimirLetra(let_A);
	if(letra=='B' or letra=='b')	imprimirLetra(let_B);
	if(letra=='C' or letra=='c')	imprimirLetra(let_C);
	if(letra=='D' or letra=='d')	imprimirLetra(let_D);
	if(letra=='E' or letra=='e')	imprimirLetra(let_E);
	if(letra=='F' or letra=='f')	imprimirLetra(let_F);
	if(letra=='G' or letra=='g')	imprimirLetra(let_G);
	if(letra=='H' or letra=='h')	imprimirLetra(let_H);
	if(letra=='I' or letra=='i')	imprimirLetra(let_I);
	if(letra=='J' or letra=='j')	imprimirLetra(let_J);
	if(letra=='K' or letra=='k')	imprimirLetra(let_K);
	if(letra=='L' or letra=='l')	imprimirLetra(let_L);
	if(letra=='M' or letra=='m')	imprimirLetra(let_M);
	if(letra=='N' or letra=='n')	imprimirLetra(let_N);
	if(letra=='O' or letra=='o')	imprimirLetra(let_O);
	if(letra=='P' or letra=='p')	imprimirLetra(let_P);
	if(letra=='Q' or letra=='q')	imprimirLetra(let_Q);
	if(letra=='R' or letra=='r')	imprimirLetra(let_R);
	if(letra=='S' or letra=='s')	imprimirLetra(let_S);
	if(letra=='T' or letra=='t')	imprimirLetra(let_T);
	if(letra=='U' or letra=='u')	imprimirLetra(let_U);
	if(letra=='V' or letra=='v')	imprimirLetra(let_V);
	if(letra=='W' or letra=='w')	imprimirLetra(let_W);
	if(letra=='X' or letra=='x')	imprimirLetra(let_X);
	if(letra=='Y' or letra=='y')	imprimirLetra(let_Y);
	if(letra=='Z' or letra=='z')	imprimirLetra(let_Z);
}

void imprimirLetra(char letra[9][9]){
	int i,j,num;
	num = rand() % 6;
	pintarPantalla(num);

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			printf("%c",letra[i][j]);
		}
		printf("\n");
	}
	sleep(2);
	system("cls");
}

void pintarPantalla(int num){
	if(num==0) 	system("color 20");
	if(num==1)	system("color 30");
	if(num==2)	system("color 50");
	if(num==3)	system("color 60");
	if(num==4)	system("color 90");
	if(num==5)	system("color A0");
	if(num==6)	system("color D0");
}