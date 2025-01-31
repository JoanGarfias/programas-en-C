#include <stdio.h>

void explicar_programa();
void leer_valores(float *r, float *v);
float calcular(float resistencia, float voltaje);
void imprimir_respuesta(float intensidad);

int main(){
	float resistencia, voltios, intensidad;
	
	explicar_programa();
	leer_valores(&resistencia, &voltios);
	intensidad = calcular(resistencia, voltios);
	imprimir_respuesta(intensidad);

	return 0;
}

void explicar_programa(){
	printf("\nEste programa calcula el valor de la intensidad");
	printf("\nen amperios. Debera introducir el valor de la");
	printf("\nresistencia y el voltaje en voltios");
	return;
}

void leer_valores(float *resis, float *volta){
	do{
		printf("\n\nIntroduce el valor de la resistencia: \n--> ");
		scanf("%f", resis);
		printf("\nIntroduce el valor del voltaje \n--> ");
		scanf("%f", volta);
	}while(*resis<=0 || *volta<=0);
}

float calcular(float resistencia, float voltaje){
	return voltaje / resistencia;
}

void imprimir_respuesta(float intensidad){
	printf("\nLa intensidad es: %f", intensidad);
}