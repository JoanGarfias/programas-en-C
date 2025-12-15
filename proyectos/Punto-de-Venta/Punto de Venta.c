#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#define TMC 64

#define VALIDAR_ID 			1
#define VALIDAR_NOMBRE 		2
#define VALIDAR_MODELO 		3
#define VALIDAR_PRECIO 		4
#define VALIDAR_DESCUENTO 	5

#define ERROR_DATOS 1
#define ERROR_INTERNO 2

#define IMPUESTO 16

#define SALIR '0'


int contProds = 0;
int contCupones = 0;

struct producto{
	unsigned int id;
	char nombre[TMC];
	char modelo[TMC];
	float precio;
	unsigned int descuento;
};
typedef struct producto PRODUC;

struct compraProducto{ //Un solo producto
	unsigned int id;
	char nombre[TMC];
	float precio;
	unsigned int cantidad;
};
typedef struct compraProducto COMPRAIND;

struct fechaAct{
	unsigned int dia;
	unsigned int mes;
	unsigned int anio;
};
typedef struct fechaAct FECHA;

struct pago{
	COMPRAIND *compras;
	FECHA fecha;
	float total;
};
typedef struct pago COMPRAS;

struct cupon{
	char codigo[12];
	unsigned int expiracion;
	char tipo[12];
	FECHA fecha;
	unsigned int descuento;
};
typedef struct cupon CUPON;

unsigned int archivoVacio(FILE *);
PRODUC * cargarDatos(PRODUC *);
void setColor(WORD);
void enviarError(int);
void vaciarCadena(char *);
unsigned int contDigs(unsigned int);

PRODUC *agregarProducto(PRODUC *);
void verProductos(PRODUC *);
int validarNuevoProducto(PRODUC, int);

void generarCompra(PRODUC *);
CUPON *cargarCupones(CUPON *);
CUPON *agregarCupon(CUPON *);
int validarFechaCupon(FECHA, FECHA);
int aplicarDescuento(COMPRAS *, char *);
void verCupones();
void guardarCupones();

void menuExtra(char *);

PRODUC *Productos;
CUPON *Cupones;

int main(){
	char opcion;
	Productos = cargarDatos(Productos);
	Cupones = cargarCupones(Cupones);

	do{
		do{
			system("cls");	setColor(14);
			printf("\n\t\t____________________________________\n");
			printf("\n\t\t\tMENU DE SELECCION");
			printf("\n\t\t____________________________________\n\n");
			setColor(11);
			printf("\n\t\t1) Productos");
			printf("\n\t\t2) Agregar Compra");
			printf("\n\t\t3) Cupones");
			printf("\n\t\t0) Salir\n\t\t--> ");
			fflush(stdin);
			scanf("%c",&opcion);
			if(opcion<'0' || opcion>'3'){
				setColor(4);
				printf("\n\tERROR: No es una opcion valida\n\n");
				system("PAUSE");
			}
			setColor(15);
		}while(opcion<'0' || opcion>'3');
		
		switch(opcion){
			case '1': //Nuevo producto
				menuExtra("productos");
				break;
			case '2':
				generarCompra(Productos);
				break;
			case '3':
				menuExtra("cupones");
				break;
			default:
				break;
		}
		printf("\n\n");
		system("PAUSE");
	}while(opcion != SALIR);
	
	guardarCupones();
	
	free(Productos);
	return 0;
}

void menuExtra(char *auxiliar){
	int opcion;
	int principal = (strcmp(auxiliar, "productos")==0)? 1 : (strcmp(auxiliar, "cupones")==0)? 2 : 3; 
	
	system("CLS");
	
	do{
		printf("\n1.- Ver %s",auxiliar);
		printf("\n2.- Agregar %s \n-->",auxiliar);
		scanf("%d",&opcion);
		if(opcion<1 || opcion>3){
			printf("\nERROR: No es valido");
		}
	}while(opcion<1 || opcion>3);
	switch(principal){
		case 1:
			switch(opcion){
				case 1:
					verProductos(Productos);
					break;
				case 2:
					Productos = agregarProducto(Productos);
					break;
				case 3:
					break;
			}
			break;
		case 2:
			switch(opcion){
				case 1: //Agregar cupon
					verCupones(Cupones);
					break;
				case 2: //Ver cupones
					agregarCupon(Cupones);
					break;
				case 3:
					break;
			}
			break;
		case 3:
			switch(opcion){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
			}
			break;
	}
	return;
}

void guardarCupones(){
	FILE *cupones_db = fopen("Database\\cupones.txt", "w+");
	int i;
	for(i=0; i<contCupones; i++){
		if(strcmp(Cupones[i].codigo, "null") == 0){
			setColor(13);
			printf("\n\nHe borrado un cupon %s", Cupones[i].codigo);
			continue;
		}
		fprintf(cupones_db, "%u %s %s %u %d %d %d", Cupones[i].descuento, Cupones[i].codigo,
			Cupones[i].tipo, Cupones[i].expiracion,
			Cupones[i].fecha.dia, Cupones[i].fecha.mes, Cupones[i].fecha.anio );
		if(i != contCupones-1){
			fprintf(cupones_db, "\n");
		}
	}
	return;
}


void verCupones(){
	int i;
	if(contCupones >= 1){
		setColor(10);
		printf("\nSe encontraron (%d) cupones! ", contCupones);
		setColor(15);
		for(i=0; i<contCupones; i++){
			setColor(11);
			printf("\n\n%s -> Tipo: %s", Cupones[i].codigo, Cupones[i].tipo);
			setColor(15);
			if(strcmp( (Cupones+i)->tipo, "usos") == 0){
				printf("\nUsos restantes: %u", Cupones[i].expiracion);
			}
			else{
				printf("\nCaduca el: %d / %d / %d", Cupones[i].fecha.dia, Cupones[i].fecha.mes, Cupones[i].fecha.anio);
			}
			printf("\nDescuento: %u %%", Cupones[i].descuento);
		}
	}
	else{
		printf("\nNo se encontraron cupones en la base de datos. ");
		system("PAUSE");
	}
}

CUPON *agregarCupon(CUPON *cupones){
	int Validacion = 0, lineas = 0;
	cupones = (CUPON *) realloc((void*)cupones, sizeof(CUPON) * (contCupones+1));
	
	time_t ahora = time(NULL);
	struct tm *tlocal = localtime(&ahora);
	
	int dia_Act = tlocal -> tm_mday;
	int mes_Act = tlocal -> tm_mon + 1;
	int anio_Act = tlocal -> tm_year + 1900;
	
	if(cupones == NULL){
		printf("\nERROR: No hay memoria");
		abort();
	}
	printf("\nIntroduzca el nuevo cupon \n--> ");
	scanf("%s", cupones[contCupones].codigo);
	printf("\nEscriba el tipo de cupon \n");
	do{
		vaciarCadena( (cupones+contCupones)->tipo);
		printf("\n\n) Cupon con tiempo de expiracion: Escriba 'expiracion' \n");
		printf("\n\n) Cupon con limite de usos: Escriba 'usos' \n--> ");
		scanf("%s", cupones[contCupones].tipo);
		Validacion = strcmp( (cupones+contCupones)->tipo, "expiracion" );
		if(Validacion != 0){
			Validacion = strcmp( (cupones+contCupones)->tipo, "usos");
		}
		if(Validacion != 0){
			continue;
		}
	}while(Validacion != 0);
	Validacion = 0;
	if(strcmp(cupones[contCupones].tipo, "expiracion") == 0){
		do{
			cupones[contCupones].expiracion = 0;
			printf("\n\nIntroduzca la fecha limite del producto: \t");
			printf("\nDia: ");
			scanf("%d", &cupones[contCupones].fecha.dia);
			printf("\nMes: ");
			scanf("%d", &cupones[contCupones].fecha.mes);
			printf("\nAnio: ");
			scanf("%d", &cupones[contCupones].fecha.anio);
			if(cupones[contCupones].fecha.anio > anio_Act){
				Validacion = 1;
			}
			else{
				if(cupones[contCupones].fecha.mes > mes_Act){
					Validacion = 1;
				}
				else{
					if(cupones[contCupones].fecha.dia > dia_Act){
						Validacion = 1;
					}
				}
			}
			if(Validacion != 1){
				printf("\n\nERROR: La fecha no es valida");
			}
		}while(Validacion != 1);
	}
	else{
		printf("\n\nIntroduzca el limite de usos");
		scanf("%u", &cupones[contCupones].expiracion);
		cupones[contCupones].fecha.dia = 0;
		cupones[contCupones].fecha.mes = 0;
		cupones[contCupones].fecha.anio = 0;
	}
	
	printf("\nIntroduce el porcentaje de descuento: ");
	scanf("%u", &cupones[contCupones].descuento);
	
	printf("%u %s %s %u %u %u %u", cupones[contCupones].descuento, cupones[contCupones].codigo, 
		cupones[contCupones].tipo, cupones[contCupones].expiracion, 
		cupones[contCupones].fecha.dia, cupones[contCupones].fecha.mes,
		cupones[contCupones].fecha.anio);
	
	FILE *db_cupones = fopen("Database\\cupones.txt", "r");
	if(!archivoVacio(db_cupones)){
		fprintf(db_cupones, "\n");
	}
	fclose(db_cupones);
	
	db_cupones = fopen("Database\\cupones.txt", "a");
	fprintf(db_cupones, "%u %s %s %u %u %u %u", cupones[contCupones].descuento,
		cupones[contCupones].codigo, cupones[contCupones].tipo, cupones[contCupones].expiracion, 
		cupones[contCupones].fecha.dia, cupones[contCupones].fecha.mes,
		cupones[contCupones].fecha.anio);
	
	fclose(db_cupones);
	contCupones++;
}

CUPON *cargarCupones(CUPON *cupones){
	int lineas = 0;
	FILE * cuponesTXT = fopen("Database\\cupones.txt", "r");
	
	if(!archivoVacio(cuponesTXT) ){
		rewind(cuponesTXT);
		cupones = (CUPON *) calloc(1, sizeof(CUPON));
	    while (fscanf(cuponesTXT, "%u %s %s %u %d %d %d", &cupones[lineas].descuento ,
		 &cupones[lineas].codigo, &cupones[lineas].tipo,  &cupones[lineas].expiracion,
		 &cupones[lineas].fecha.dia, &cupones[lineas].fecha.mes, &cupones[lineas].fecha.anio) != EOF){
	        lineas++;
	        cupones = (CUPON *) realloc((void*)cupones, sizeof(CUPON) * (lineas + 1));
	        if(cupones == NULL){
	            printf("\n\nERROR");
	            exit(-1);
	        }
	    }
		contCupones = lineas;
	}
	else{
		return NULL;
	}
	
	fclose(cuponesTXT);
	return cupones;
}

void generarCompra(PRODUC *prods){
	system("cls");
	int cont = 0, descuentoActivo=0;
	char cupon[12];
	
	time_t ahora = time(NULL);
	struct tm *tlocal = localtime(&ahora);
	
	char comando[TMC];
	unsigned int codigo;
	int i,j;
	
	COMPRAS PAGO;
	PAGO.compras = (COMPRAIND*) calloc(1, sizeof(COMPRAIND));
	PAGO.total = 0.0;
	PAGO.fecha.dia = tlocal -> tm_mday;
	PAGO.fecha.mes = tlocal -> tm_mon + 1;
	PAGO.fecha.anio = tlocal -> tm_year + 1900;
	do{
		PAGO.compras = (COMPRAIND *) realloc((void*)PAGO.compras, sizeof(COMPRAIND) * (cont+1) );
		printf("\nIntroduce el ID del producto: \n--> ");
		scanf("%u",&PAGO.compras[cont].id);
		fflush(stdin);
		printf("\nIntroduce la cantidad del producto: \n--> ");
		fflush(stdin);
		scanf("%u",&PAGO.compras[cont].cantidad);
		for(i=0; i<contProds; i++){
			if(PAGO.compras[cont].id == prods[i].id){
				strcpy( PAGO.compras[cont].nombre , (prods+i)->nombre );
				PAGO.compras[cont].precio = prods[i].precio;
			}
		}
		cont++;
		printf("\n____COMANDO____ : \t ");
		fflush(stdin);
		gets(comando);
	}while(strcmp(comando, "salir") != 0);
	
	for(i=0; i<cont; i++){
		for(j=0; j<contProds; j++){
			if( PAGO.compras[i].id == prods[j].id){
				PAGO.total += PAGO.compras[i].precio * PAGO.compras[i].cantidad;
			}
		}
	}
	
	printf("\n\nDesea agregar un cupon de descuento? \n--> ");
	gets(cupon);
	
	if( (descuentoActivo = aplicarDescuento(&PAGO, cupon)) != 0 ){
//		Cupones[i].expiracion--;
		PAGO.total = PAGO.total - (PAGO.total * (descuentoActivo / 100.0));
		setColor(13);
		printf("\nSe aplico el cupon %s a tu compra \n", cupon);
		system("PAUSE");
		setColor(15);
	}
	else{
		setColor(14);
		printf("\nERROR: El codigo proporcionado no es valido");
		system("PAUSE");
		setColor(15);
	}

	system("cls");
	printf("\nFecha de Compra: %02d / %02d / %d",PAGO.fecha.dia, PAGO.fecha.mes, PAGO.fecha.anio);
	printf("\n_________________________________________________________________________\n\n");
	printf("\nNOMBRE                CANTIDAD    PRECIO");
	for(i=0; i<cont; i++){
		printf("\n%s", PAGO.compras[i].nombre);
		for(j=1; j<16+(16/strlen(PAGO.compras[i].nombre) ); j++){
			printf(" ");
		}
		printf("%u", PAGO.compras[i].cantidad);
		for(j=1; j<=12-contDigs(PAGO.compras[i].cantidad); j++){
			printf(" ");
		}
		printf("%f", PAGO.compras[i].precio * PAGO.compras[i].cantidad);
	}
	printf("\n________________________________________________________________________\n\n");
	if(descuentoActivo){
		printf("\n\tDESCUENTO: %u %%", descuentoActivo);
	}
	printf("\n\tTOTAL: %f",PAGO.total);
	printf("\n\n\n");
	free(PAGO.compras);
}

int validarFechaCupon(FECHA f1, FECHA f2){
	/* F1 es la fecha de la compra
		F2 es la fecha de caducidad del cupon
	*/
	if(f1.anio <= f2.anio){
		if(f1.mes <= f2.mes){
			if(f1.dia <= f2.dia){
				return 1;
			}
		}
	}
	return 0;
	
}

int aplicarDescuento(COMPRAS *compraTemp, char *codigo){
	int i;
	for(i=0; i<contCupones; i++){
		if(strcmp(codigo, (Cupones+i)->codigo) == 0){
			if(strcmp((Cupones+i)->tipo, "usos") == 0 && Cupones[i].expiracion > 0){
				Cupones[i].expiracion--;
				return Cupones[i].descuento;
			}
			else{
				if(validarFechaCupon(compraTemp->fecha, Cupones[i].fecha) ){
					return Cupones[i].descuento;
				}
			}
			strcpy(Cupones[i].codigo, "null");
			guardarCupones();
		}
	}
	return 0;
}

PRODUC *cargarDatos(PRODUC *prods){
	int lineas = 0;
	FILE * prodsTXT = fopen("Database\\productos.txt", "r");
	
	if(!archivoVacio(prodsTXT) ){
		rewind(prodsTXT);
		prods = (PRODUC *) calloc(1, sizeof(PRODUC));
	    while (fscanf(prodsTXT, "%u %s %s %f %u", &prods[lineas].id,
				prods[lineas].nombre, prods[lineas].modelo, &prods[lineas].precio, &prods[lineas].descuento) != EOF){
	        lineas++;
	        prods = (PRODUC *) realloc((void*)prods, sizeof(PRODUC) * (lineas + 1));
	        if(prods == NULL){
	            printf("\n\nERROR");
	            exit(-1);
	        }
	    }
		contProds = lineas;
	}
	else{
		return NULL;
	}
	
	fclose(prodsTXT);
	return prods;
}


int validarNuevoProducto(PRODUC temp, int id){
	int i, aux;
	switch(id){
		case VALIDAR_ID:
			aux = contDigs(temp.id);
			if(aux!=7){
				return 0;
			}
			break;
		case VALIDAR_NOMBRE:
			for(i=0; i<strlen(temp.nombre); i++){
				if(isalpha(temp.nombre[i]) || isdigit(temp.nombre[i]) || temp.nombre[i]=='\n'){
					continue;
				}
				else{
					return 0;
				}
			}
			break;
		case VALIDAR_MODELO:
			aux = strlen(temp.modelo);
			if(aux==1 && temp.modelo[0]=='0'){
				return 1;
			}
			else{
				if(aux>7){
					return 0;
				}
			}
			break;
	}
	return 1;
}

void verProductos(PRODUC *Productos){
	int i;
	char desc;
	for(i=0; i<contProds; i++){
		printf("\n______________________\n\n");
		printf(" Nombre: %s\n ID: %u\n Modelo: %s\n Precio: %f\n",
			Productos[i].nombre, Productos[i].id, Productos[i].modelo, Productos[i].precio);
		if(Productos[i].descuento > 0){
			printf(" Descuento: %u %%\n",Productos[i].descuento);
		}
		printf("______________________\n");
	}
}

unsigned int contDigs(unsigned int num){
	if(num<10)
		return 1;
	return 1 + contDigs(num/10);
}

unsigned int archivoVacio(FILE *temp){
	if(temp == NULL){
		printf("Error");
		exit(-1);
	}
	fseek(temp, 0, SEEK_END);
	if (ftell(temp)!=0){
		return 0;
	}
	rewind(temp);
	return 1;
}

PRODUC *agregarProducto(PRODUC *prods){
	int aux;
	int Verificado = 0;

	system("cls");
	prods = (PRODUC *) realloc((void*) prods, sizeof(PRODUC) * (contProds + 1));
	do{
		printf("\nIngrese el nombre del producto \n--> ");
		fflush(stdin);
		fgets(prods[contProds].nombre, TMC, stdin);
		if(prods[contProds].nombre[0]=='\n' || ( (int)strlen((prods+contProds)->nombre) ) <= 5){
			enviarError(ERROR_DATOS);
		}
	}while(prods[contProds].nombre[0]=='\n' || ( (int)strlen((prods+contProds)->nombre) ) <= 5);
	prods[contProds].nombre[strlen(prods[contProds].nombre)-1] = '\0';
	
	do{
		printf("\nIngrese el ID del producto \n--> ");
		scanf("%u",&prods[contProds].id);
		fflush(stdin);
		Verificado = validarNuevoProducto(*(prods+contProds), VALIDAR_ID);
		if(!Verificado){
			enviarError(ERROR_DATOS);
		}
	}while(!Verificado);

	do{
		printf("\nIngrese el Modelo del producto \n--> ");
		fflush(stdin);
		fgets(prods[contProds].modelo, TMC, stdin);
		Verificado = validarNuevoProducto(*(prods+contProds), VALIDAR_MODELO);
		if(!Verificado){
			enviarError(ERROR_DATOS);
			vaciarCadena( (prods+contProds)->modelo);
		}
	}while(!Verificado);
	prods[contProds].modelo[strlen(prods[contProds].modelo)-1] = '\0';
	if(prods[contProds].modelo[0]=='\0'){
		strcpy( (prods+contProds)->modelo, "N/A");
	}
	
	do{
		printf("\nIngrese el Precio del producto \n--> ");
		fflush(stdin);
		aux = scanf("%f",&prods[contProds].precio);
		if(prods[contProds].precio<=0 || aux==0){
			enviarError(ERROR_DATOS);
		}
	}while(prods[contProds].precio<=0 || aux==0);
	
	do{
		printf("\nIngrese el Descuento del producto (0 Si no hay Descuento)\n--> ");
		fflush(stdin);
		aux = scanf("%u",&prods[contProds].descuento);
		if(prods[contProds].descuento>=100 || aux==0){
			enviarError(ERROR_DATOS);
		}
	}while(prods[contProds].descuento>=100 || aux==0);
	
	FILE *prodsTXT = fopen("Database\\productos.txt", "a");
	if(!archivoVacio(prodsTXT)){
		fprintf(prodsTXT,"\n");
	}
	fprintf(prodsTXT, "%u %s %s %f %u",
		prods[contProds].id, prods[contProds].nombre, 
		prods[contProds].modelo, prods[contProds].precio, prods[contProds].descuento);
	fclose(prodsTXT);
	
	contProds++;
	return prods;
}

void vaciarCadena(char *cadena){
	int i;
	for(i=0; i<strlen(cadena); i++){
		cadena[i] = '\0';
	}
	return;
}

void enviarError(int ErrorId){
	setColor(4);
	switch(ErrorId){
		case ERROR_DATOS:
			printf("\n\n\tERROR: Ha sucedido un problema con los datos proporcionados\n\n");
			break;
		case ERROR_INTERNO:
			printf("\n\n\tERROR: Ha sucedido una excepcion en el programa\n\n");
			break;
	}
	system("PAUSE");	setColor(15);
	return;
}

void setColor(WORD col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),col);
}