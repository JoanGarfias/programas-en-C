/*
Programa que lee una cadena de forma dinamica, y luego cuenta los numeros
que hay, las vocales y consonantes

ocupar funciones
*/

#include <stdio.h>
#include <stdlib.h>

int esNumero(char);
int esVocal(char);
int esConsonante(char);

int main(){
	int i;
	int cont = 0;
	char aux;
	//char *texto = (char *) malloc(sizeof(int));
	char *texto = (char *) calloc(1, sizeof(char));
	
	do{
		aux = getchar();
		if(aux=='\n')
			break;
		texto = (char *) realloc(texto, sizeof(char) * (cont+1));
		*(texto+cont) = aux;
		cont++;
	}while(aux!='\n');
	printf("\nYa deje de leer valores");
	getchar();
	printf("%s", texto);
	int contNums=0, contConso=0, contVocal=0;
	
	for(i=0; i<cont; i++){
		if(esNumero( *(texto+i) ) ){
			contNums++;
		}
		else{
			if(esVocal(texto[i])){
				contVocal++;
			}
			else{
				if(esConsonante(texto[i])){
					contConso++;
				}
			}
		}
	}
	
	printf("\n\n");
	printf("\nNumeros: %d", contNums);
	printf("\nVocales: %d", contVocal);
	printf("\nConsonantes: %d", contConso);
	
	return 0;
}

int esNumero(char temp){
	return (temp >= '0' && temp<='9')? 1 : 0;
}

int esVocal(char temp){
	return (temp=='a' || temp=='e' || temp=='i' || temp=='o' || temp=='u')? 1 : 0;
}

int esConsonante(char temp){
	return (!esVocal(temp) && !esNumero(temp)
	 && ( (temp>='a' && temp<='z') || (temp>='A'&&temp<='Z') ) )? 1 : 0;
}