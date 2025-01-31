#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.h"

#define TMC 32

struct alumno{
	char nombre[TMC];
	char apellidos[TMC];
	int edad;
	float promedio;
	unsigned int matricula;
};
typedef struct alumno ALUMNO;

void cargarDatos();
void agregarAlumno();
void mostrarAlumnos();
void buscarAlumno();
void modificarAlumno();
void eliminarAlumno();

/*Funciones auxiliares*/
unsigned int archivoValido();
unsigned int campoValido(ALUMNO, unsigned int);
unsigned int contDigs(int);
unsigned int pedirMatricula();
void limpiarString(unsigned int);
ALUMNO pedirDatos(unsigned int);
void cuadroHonor();
ALUMNO * copiarDatos();
float calcMayor(ALUMNO *);
void imprimirCuadro(ALUMNO *, float);
void test(ALUMNO *, float, unsigned int);

ALUMNO * alm = NULL; //Almacenará todos los datos de los alumnos durante la ejecución del programa
int contAlms = 0;

int main(){
	char op;
	do{
		system("color f");
		do{
			system("cls");
			cargarDatos();
			printf("\n\n\t\tBIENVENIDO AL SISTEMA DE ALUMNOS");
			printf("\n\n\t\tESCOJA UNA OPCION:");
			printf("\n\t1.- Agregar alumno");
			printf("\n\t2.- Ver alumnos");
			printf("\n\t3.- Buscar alumno");
			printf("\n\t4.- Eliminar alumno");
			printf("\n\t5.- Modificar alumno");
			printf("\n\t6.- Cuadro de Honor");
			printf("\n\t7.- Salir");
			printf("\n\tSeleccion: ");
			scanf("%c",&op);
		if(op-'0'<1 || op-'0'>7){
				system("cls");
				printf("\n\tERROR: Escoja una opcion valida");
			}
		}while(op-'0'<1 || (op-'0')>7);
		switch(op){
			case '1':
				agregarAlumno();
				break;
			case '2':
				mostrarAlumnos();
				break;
			case '3':
				buscarAlumno();
				break;
			case '4':
				eliminarAlumno();
				break;
			case '5':
				modificarAlumno();
				break;
			case '6':
				cuadroHonor();
				break;
			default:
				exit(0);
		}
		getch();
	}while(!isdigit(op) || op-'0'!=7);
	
	free(alm);
	
	return 0;
}

void agregarAlumno(){
	ALUMNO alumno;
	FILE * datos = fopen("datos.txt", "a");
	system("cls");
	system("color a");
	alumno = pedirDatos(PEDIR);
	
	contAlms++;
	alm = (ALUMNO *) realloc(alm , sizeof(ALUMNO) * contAlms);
	strcpy(alm[contAlms-1].nombre, alumno.nombre);
	strcpy(alm[contAlms-1].apellidos, alumno.apellidos);
	alm[contAlms-1].matricula = alumno.matricula;
	alm[contAlms-1].edad = alumno.edad;
	alm[contAlms-1].promedio = alumno.promedio;
	
	fprintf(datos, "\n%s %s %u %d %f",alumno.nombre,alumno.apellidos,alumno.matricula, alumno.edad, alumno.promedio);
	fclose(datos);
}

void cargarDatos(){
	int lineas = 0;
	
	if( archivoValido() ){
		FILE * datos = fopen("datos.txt", "r");
		alm = (ALUMNO *) realloc(alm, sizeof(ALUMNO) * 1);
		if(datos == NULL){
			printf("\n\nERROR");
			exit(-1);
		}
	    while (fscanf(datos, "%s %s %u %d %f", alm[lineas].nombre, alm[lineas].apellidos, &alm[lineas].matricula,&alm[lineas].edad, &alm[lineas].promedio) != EOF){
	        lineas++;
	        alm = (ALUMNO *) realloc(alm, sizeof(ALUMNO) * (lineas + 1));
	        if(alm == NULL){
	            printf("\n\nERROR");
	            exit(-1);
	        }
	    }
		contAlms = lineas;
		fclose(datos);
	}
}

unsigned int archivoValido(){
	FILE *temp = fopen("datos.txt", "r");
	if(temp == NULL){
		printf("Error");
		exit(-1);
	}
	fseek(temp, 0, SEEK_END);
	if (ftell(temp)!=0){
		fclose(temp);
		return 1;
	}
	fclose(temp);
	return 0;
}

void mostrarAlumnos(){
	int i;
	system("cls");
	system("color e");
	if(contAlms > 0){
		for(i=0; i<contAlms; i++){
			printf("\n\nNombre %s\nApellidos: %s\nMatricula: %u\nEdad: %d\nPromedio: %.2f",alm[i].nombre, alm[i].apellidos, alm[i].matricula,alm[i].edad, alm[i].promedio);
		}
	}
	else{
		system("cls");
		printf("\n\n\tERROR : No hay alumnos registrados");
	}
}

void buscarAlumno()
{
	unsigned int matricula, matActiva = 0;
	int i=0;
	system("cls");
	system("color 6");
	if(contAlms >= 1){
		matricula = pedirMatricula();
		for(i=0; i<contAlms; i++){
			if(alm[i].matricula == matricula){
				printf("\nNombre: %s\nApellido: %s\nMatricula: %u\nEdad: %d\nPromedio: %f",alm[i].nombre, alm[i].apellidos, alm[i].matricula, alm[i].edad, alm[i].promedio);
				matActiva = 1;
				break;
			}
		}
		if(!matActiva){
			printf("\n\tERROR: No se encontro ningun alumno con esa matricula");
		}
	}
	else{
		printf("\nERROR: No hay alumnos registrados");
	}
}
void eliminarAlumno()
{
	unsigned int matricula, matActiva = 0, i=0;
	FILE * datos = fopen("datos.txt", "w");
	if(datos==NULL)	exit(-1);
	
	system("cls");
	system("color c");
	if(contAlms >= 1){
		matricula = pedirMatricula();
		for(i=0; i<contAlms; i++){
			if(alm[i].matricula == matricula)
				matActiva = 1;
		}
		if(matActiva){
			for(i=0; i<contAlms; i++){
				if(alm[i].matricula == matricula)
					continue;
				fprintf(datos, "%s %s %u %d %f\n",alm[i].nombre, alm[i].apellidos, alm[i].matricula, alm[i].edad, alm[i].promedio);
			}
			contAlms--;
		}
		else{
			system("cls");
			printf("\nNo se ha encontrado ningun alumno con esa matricula");
		}
	}
	else{
		printf("\nERROR: No hay alumnos registrados");
	}
	fclose(datos);
	cargarDatos();
}

unsigned int pedirMatricula()
{
	unsigned int matricula;
	do{
		printf("\nIngrese la matricula: \t");
		scanf("%u",&matricula);
		if(contDigs(matricula) != 5 || matricula<0){
			printf("\n\tERROR: La matricula no es valida");
		}
	}while(contDigs(matricula) != 5 || matricula<0);
	return matricula;
}

void modificarAlumno()
{
	unsigned int matriculaAux,i,j;
	ALUMNO AlmModificado;
	system("cls");
	system("color e");
	if(contAlms >= 1){
		matriculaAux = pedirMatricula();
		for(i=0; i<contAlms; i++){
			if(alm[i].matricula == matriculaAux){
				limpiarString(i);
				AlmModificado = pedirDatos(MODIFICAR);
				strcpy(alm[i].nombre, AlmModificado.nombre);
				strcpy(alm[i].apellidos, AlmModificado.apellidos);
				alm[i].edad = AlmModificado.edad;
				alm[i].promedio = AlmModificado.promedio;
				FILE *temp = fopen("datos.txt", "w");
				for(j=0; j<contAlms; j++){
					fprintf(temp, "%s %s %u %d %f\n",alm[j].nombre, alm[j].apellidos, alm[j].matricula, alm[j].edad, alm[j].promedio);
				}
				fclose(temp);	
				cargarDatos();
				break;
			}
		}
	}
	else{
		printf("\n\tERROR: Aun no hay alumnos registrados");
	}
}

int campoValido(ALUMNO temp, int TIPO)
{
	int i;
	switch(TIPO){
		case NOMBRE:
			for(i=0; i<strlen(temp.nombre); i++){
				if(isdigit(temp.nombre[i]) || !isalpha(temp.nombre[i]) || strlen(temp.nombre) <= 3){
					return 0;
				}
			}
			break;
		case APELLIDO:
			for(i=0; i<strlen(temp.apellidos); i++){
				if(isdigit(temp.apellidos[i]) || !isalpha(temp.apellidos[i]) || strlen(temp.apellidos) <= 3){
					return 0;
				}
			}
			break;
		case EDAD:
			if(temp.edad < 0 || temp.edad>100)	return 0;
			break;
		case PROMEDIO:
			if(temp.promedio < 0.0 || temp.promedio > 10.0)	return 0;
			break;
		case MATRICULA:
			if(contDigs(temp.matricula) != 5)	return 0;
			for(i=0; i<contAlms; i++){
				if(alm[i].matricula == temp.matricula)
					return 0;
			}
			break;
	}
	return 1;
}

ALUMNO pedirDatos(unsigned int TIPO)
{
	ALUMNO alumno; //temporal
	do{
		printf("\nIntroduzca el nombre: \t");
		fflush(stdin);
		scanf("%s",&alumno.nombre);
		if(!campoValido(alumno, NOMBRE)){
			system("cls");
			printf("\n\tERROR: El nombre proporcionado no es valido");
		}
	}while(!campoValido(alumno, NOMBRE));
	do{
		printf("\nIntroduzca el apellido: ");
		fflush(stdin);
		scanf("%s",&alumno.apellidos);
		if(!campoValido(alumno, APELLIDO)){
			system("cls");
			printf("\n\tERROR: El apellido proporcionado no es valido");
		}
	}while(!campoValido(alumno, APELLIDO));
	if(TIPO != MODIFICAR){
		do{
			printf("\nIntroduzca la matricula: ");
			fflush(stdin);
			scanf("%d",&alumno.matricula);
			if(!campoValido(alumno, MATRICULA)){
				system("cls");
				printf("\n\tERROR: La Matricula proporcionada no es valida o ya existe");
			}	
		}while(!campoValido(alumno, MATRICULA));
	}
	do{
		printf("\nIntroduzca la edad: ");
		fflush(stdin);
		scanf("%d",&alumno.edad);
		if(!campoValido(alumno, EDAD)){
			system("cls");
			printf("\n\tERROR: La edad proporcionada no es valida");
		}
	}while(!campoValido(alumno, EDAD));
	do{
		printf("\nIntroduzca el promedio: ");
		fflush(stdin);
		scanf("%f",&alumno.promedio);
		if(!campoValido(alumno,PROMEDIO)){
			system("cls");
			printf("\n\tERROR: El promedio no es valido");
		}
	}while(!campoValido(alumno, PROMEDIO));
	return alumno;
}

void cuadroHonor()
{
	system("cls");
	system("color b");
	if(contAlms > 1){
		float mayor;
		ALUMNO * temp = copiarDatos();
		printf("\n\nPrimer lugar: \n");
		mayor = calcMayor(temp);
		imprimirCuadro(temp, mayor);
		if(contAlms >= 2){
			printf("\n\nSegundo lugar: \n");
			mayor = calcMayor(temp);
			imprimirCuadro(temp, mayor);
		}
		if(contAlms >= 3){
			printf("\n\nTercer lugar: \n");
			mayor = calcMayor(temp);
			imprimirCuadro(temp, mayor);
		}
	}
	else{
		printf("\nNo hay suficientes alumnos");
	}
}

void limpiarString(unsigned int posicion)
{
	int i;
	for(i=0; i<strlen(alm[posicion].nombre); i++)
		alm[posicion].nombre[i] = '\0';
	for(i=0; i<strlen(alm[posicion].apellidos); i++)
		alm[posicion].apellidos[i] = '\0';
}

ALUMNO * copiarDatos(){
	ALUMNO * temp;
	temp = (ALUMNO *) malloc(sizeof(ALUMNO) * contAlms);
	int i;
	if(contAlms>1){
		for(i=0; i<contAlms; i++){
			strcpy(temp[i].nombre, alm[i].nombre);
			strcpy(temp[i].apellidos, alm[i].apellidos);
			temp[i].edad = alm[i].edad;
			temp[i].promedio = alm[i].promedio;
		}
	}
	return temp;
}

float calcMayor(ALUMNO *temp){
	int i=0;
	float mayor;
	while(i<contAlms){
		if(temp[i].promedio != -1){
			mayor = temp[i].promedio;
			break;
		}
		i++;
	}
	i=0;
	while(i<contAlms){
		if(temp[i].promedio > mayor){
			mayor = temp[i].promedio;
		}
		i++;
	}
	for(i=0; i<contAlms; i++){
		if(temp[i].promedio == mayor){
			temp[i].promedio = -1;
		}
	}
	return mayor;
}

void imprimirCuadro(ALUMNO *temp, float promCuadro){
	int i;
	for(i=0; i<contAlms; i++){
		if(alm[i].promedio == promCuadro){
			printf("\n-> %s %s %.2f",alm[i].nombre, alm[i].apellidos, alm[i].promedio);
		}
	}
}

void test(ALUMNO *temp, float promCuadro, unsigned int pos){
	if(pos<=contAlms){
		if(temp[pos].promedio == promCuadro){
			printf("\n-> %s %s %.2f",alm[pos].nombre, alm[pos].apellidos, alm[pos].promedio);
		}
		test(temp, promCuadro, pos+1);
	}
}

unsigned int contDigs(int num){
	return (num<10)?	1 : 1+contDigs(num/10);
}