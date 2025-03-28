#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N_CAPAS 7

typedef struct capa{
	char *encabezado;
	char *mensaje;
}CAPA;

void enviarMensaje(CAPA *capa, int *i, char *m){
	if(*i > 0){
		strcat(capa[*i].mensaje, capa[(*i) - 1].encabezado);
		strcat(capa[*i].mensaje, capa[(*i) - 1].mensaje);
	}
	else{
		strcpy(capa[*i].mensaje, capa[*i].encabezado);
		strcat(capa[*i].mensaje, m);
	}
	if(*i == N_CAPAS - 1){
		printf("\nMensaje enviado exitosamente");
		printf("\n%s", capa[*i].mensaje);
		return;
	}
	*i = *i + 1;
	enviarMensaje(capa, i, m);
}

int main(){
	
	CAPA *capas = (CAPA *) calloc(7, sizeof(CAPA));
	int i;
	for(i=0; i<N_CAPAS; i++){
		capas[i].encabezado = (char *) calloc(64, sizeof(char));
		capas[i].mensaje = (char *) calloc(256, sizeof(char));
	}
	
	strcpy(capas[0].encabezado, "Capa 1: Fisica\n");
	strcpy(capas[1].encabezado, "Capa 2: Enlace de Datos\n");
	strcpy(capas[2].encabezado, "Capa 3: Red\n");
	strcpy(capas[3].encabezado, "Capa 4: Transporte\n");
	strcpy(capas[4].encabezado, "Capa 5: Sesion\n");
	strcpy(capas[5].encabezado, "Capa 6: Presentacion\n");
	strcpy(capas[6].encabezado, "Capa 7: Aplicacion\n");
	
	i=0;
	
	char mensaje[] = "user=500&pass=holamundo&len=US";
	printf("\nEl mensaje que se enviara a las capas es: %s\n", mensaje);
	enviarMensaje(capas, &i, mensaje);
	
	return 0;
}