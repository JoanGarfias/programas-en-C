#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SALIR 10

typedef struct resistencia{
	char **valores;
	int tam;
}RESIST;

void cleanArr(char **);
RESIST leer(RESIST *);
void verResistencia(RESIST);

char * calcOhms(RESIST);
char * calcResist(char *);

char hallarValor(char *);
float hallarMultiplicador(char *);
float hallarTolerancia(char *);

char *hallarColor(float);
char *obtenerCeros(char *);

int main(){
	int opcion, i;
	RESIST resist;
	char *result;
	char *expresion = (char *) calloc(16, sizeof(char));
	resist.tam = 0;
	do{
		system("CLS");	
		printf("\n1) Verificar Resistencia por Nombre/Codigo");
		printf("\n2) Verificar Resistencia por Valor Numerico");
		printf("\n3) Ver Resistencia agregada");
		printf("\n10) Salir\n--> ");
		scanf("%d", &opcion);
		
		switch(opcion){
			case 1:
				resist = leer(&resist);
				result = calcOhms(resist);
				verResistencia(resist);
				printf("\nEquivalente en ohms es: %s", result);
				break;
			case 2:
				printf("\nIngrese la expresion: \n");
				fflush(stdin);
				gets(expresion);
				result = calcResist(expresion);
				printf("\nLos colores son : \n--> %s", result);
				break;
			case 3:
				verResistencia(resist);
				break;
			default:
				break;
		}
		printf("\n\n");
		system("PAUSE");
	}while(opcion != SALIR);
	opcion = resist.tam;
	
	for(i=0; i<opcion; i++){
		free(resist.valores[i]);
	}
	
	return 0;
}

RESIST leer(RESIST *resist){
	int i;
	
	printf("\nIntroduzca el numero de bandas: \n--> ");
	scanf("%d", &resist->tam);
	
	resist->valores = (char **) calloc(resist->tam, sizeof(char *));
	
	for(i=0; i<resist->tam; i++){
		fflush(stdin);
		resist->valores[i] = (char *) calloc(12, sizeof(char *));
		printf("\nIntroduzca el color %i \n--> ", i+1);
		gets(resist->valores[i]);
	}
	return *resist;
}

void verResistencia(RESIST resist){
	int i, j;
	if(resist.tam <= 0){
		return;
	}
	
	printf("\n\nLa ultima resistencia agregada es: \n");
	for(i=0; i<resist.tam; i++){
		for(j=0; j<(int)strlen(resist.valores[i]); j++){
			printf("%c", resist.valores[i][j]);
		}
		printf(" : ");
	}
}


char hallarValor(char *valor){
	if(strcmp(valor, "negro") == 0){
		return '0';
	}
	else if(strcmp(valor, "marron") == 0){
		return '1';
	}
	else if(strcmp(valor, "rojo") == 0){
		return '2';
	}
	else if(strcmp(valor, "naranja") == 0){
		return '3';
	}
	else if(strcmp(valor, "amarillo") == 0){
		return '4';
	}
	else if(strcmp(valor, "verde") == 0){
		return '5';
	}
	else if(strcmp(valor, "azul") == 0){
		return '6';
	}
	else if(strcmp(valor, "violeta") == 0){
		return '7';
	}
	else if(strcmp(valor, "gris") == 0){
		return '8';
	}
	else if(strcmp(valor, "blanco") == 0){
		return '9';
	}
}

float hallarMultiplicador(char *valor){
	if(strcmp(valor, "oro") == 0){
		return 0.1;
	}
	else if(strcmp(valor, "plata") == 0){
		return 0.01;
	}
	else if(strcmp(valor, "negro") == 0){
		return 1.0;
	}
	else if(strcmp(valor, "marron" ) == 0){
		return 10.0;
	}
	else if(strcmp(valor, "rojo") == 0){
		return 100.0;
	}
	else if(strcmp(valor, "naranja") == 0){
		return 1000.0;
	}
	else if(strcmp(valor, "amarillo") == 0){
		return 10000.0;
	}
	else if(strcmp(valor, "verde") == 0){
		return 100000.0;
	}
	else if(strcmp(valor, "azul") == 0){
		return 1000000.0;
	}
	else if(strcmp(valor, "violeta") == 0){
		return 10000000.0;
	}
	else if(strcmp(valor, "gris") == 0){
		return 100000000.0;
	}
	else if(strcmp(valor, "blanco") == 0){
		return 1000000000.0;
	}
}

float hallarTolerancia(char *valor){
	if(strcmp(valor, "marron") == 0){
		return 1.0;
	}
	else if(strcmp(valor, "rojo") == 0){
		return 2.0;
	}
	else if(strcmp(valor, "verde") == 0){
		return 0.5;
	}
	else if(strcmp(valor, "azul") == 0){
		return 0.25;
	}
	else if(strcmp(valor, "violeta") == 0){
		return 0.1;
	}
	else if(strcmp(valor, "gris") == 0){
		return 0.05;
	}
	else if(strcmp(valor, "oro") == 0){
		return 5.0;
	}
	else if(strcmp(valor, "plata") == 0){
		return 10.0;
	}
	else if(strcmp(valor, "negro") == 0){
		return 20.0;
	}
}

char* obtenerColor(float valor) {
    if(valor == 1.0) {
        return "marron";
    }
    else if(valor == 2.0) {
        return "rojo";
    }
    else if(valor == 5.0) {
        return "verde";
    }
    else if(valor == 6.0) {
        return "azul";
    }
    else if(valor == 7.0) {
        return "violeta";
    }
    else if(valor == 8.0) {
        return "gris";
    }
    else if(valor == 0.0) {
        return "negro";
    }
    else if(valor == 3.0){
    	return "naranja";
	}
	else if(valor == 4.0){
		return "amarillo";
	}
	else if(valor == 9.0){
		return "blanco";
	}
    else {
        return "ER";
    }
}

char *obtenerCeros(char *exp){
	int cantidad = 0;
	char *aux = exp;
	while(*aux == '0'){
		cantidad++;
		aux += 1;
	}
    if(cantidad == 0) {
        return "negro";
    }
    else if(cantidad == 1) {
        return "marron";
    }
    else if(cantidad == 2) {
        return "rojo";
    }
    else if(cantidad == 3) {
        return "naranja";
    }
    else if(cantidad == 4) {
        return "amarillo";
    }
    else if(cantidad==5){
    	return "verde";
	}
	else if(cantidad ==6){
		return "azul";
	}
	else if(cantidad == 7){
		return "violeta";
	}
	else if(cantidad == 8){
		return "gris";
	}
	else if(cantidad ==9){
		return "blanco";
	}
    // y así sucesivamente para otras cantidades de ceros
    else {
        return "cantidad invalida";
    }
}

char* calcOhms(RESIST resist){
	int i;
	char *cad = (char *) calloc(32, sizeof(char));
	
	float multiplicador = 1.0;
	float tolerancia = 0.0;
	
	float temp = 1.0;
	
	int tamCad = 0;
	if(resist.tam == 4){
		cad[0] = hallarValor(resist.valores[0]);
		cad[1] = hallarValor(resist.valores[1]);
		multiplicador = hallarMultiplicador(resist.valores[2]);
		tolerancia = hallarTolerancia(resist.valores[3]);
		temp = atof(cad);
		cleanArr(&cad);
		temp *= multiplicador;
		sprintf(cad, "%.3f ohms con %.2f%% de tolerancia", temp, tolerancia);
	}
	else if(resist.tam == 5){
		cad[0] = hallarValor(resist.valores[0]);
		cad[1] = hallarValor(resist.valores[1]);
		cad[2] = hallarValor(resist.valores[2]);
		multiplicador = hallarMultiplicador(resist.valores[3]);
		tolerancia = hallarTolerancia(resist.valores[4]);
		temp = atof(cad);
		cleanArr(&cad);
		temp *= multiplicador;
		sprintf(cad, "%.3f ohms con %.2f%% de tolerancia", temp, tolerancia);
	}
	else if(resist.tam == 3){
		cad[0] = hallarValor(resist.valores[0]);
		cad[1] = hallarValor(resist.valores[1]);
		multiplicador = hallarMultiplicador(resist.valores[2]);
		temp = atof(cad);
		cleanArr(&cad);
		temp *= multiplicador;
		sprintf(cad, "%.3f ohms con 20%% de tolerancia", temp, tolerancia);
	}
	
	return cad;
}

char * calcResist(char *exp){
	int i;
	char *bands = (char *) calloc(92, sizeof(char));
	float v1 = 0.0, v2=0.0, v3 = 0.0, multiplicador = 1.0, temp = 1.0;
	int value = atoi(exp);
	int digs = 0;
	while(value > 0){
		digs++;
		value /= 10;
	}
		
	if (digs <= 2) {
        /* Caso de resistencia de 2 bandas */
        sprintf(bands, "%s%s", bands, obtenerColor(value / 10 * 1.0) );
        sprintf(bands, "%s%s", bands, obtenerColor(value % 10 * 1.0) );
    }
    else if (digs == 3) {
        /* Caso de resistencia de 3 bandas */
        sprintf(bands, "%s %s", bands, obtenerColor(value / 100.0) );
        sprintf(bands, "%s %s", bands, obtenerColor((value /10) % 10 * 1.0) );
        sprintf(bands, "%s %s", bands, obtenerCeros(exp+2));
    }


/*
	
	sprintf(cadena,"%s %s", cadena,obtenerColor((exp[0]-'0')*1.0) );
	sprintf(cadena, "%s %s", cadena,obtenerColor((exp[1]-'0')*1.0));
	sprintf(cadena, "%s %s", cadena,obtenerCeros(exp+2));
*/
	return bands;
}

void cleanArr(char **var){
	int i;
	for(i=0; i<(int)strlen((*var)); i++){
		*(*(var+i)) = '\0';
	}
}