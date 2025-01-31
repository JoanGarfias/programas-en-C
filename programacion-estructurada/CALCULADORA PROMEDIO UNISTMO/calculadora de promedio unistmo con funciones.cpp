#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define PER 5
#define MAT 5

void pedirDatos(double boleta[MAT+1][PER], char mat[MAT][50]);
void mostrarDatos(double boleta[MAT+1][PER], char mat[MAT][50]);

int main(){
	int i,j;
	char mat[MAT][50];
	double boleta[MAT+1][PER]; //MAT+1 es porque el promedio final es la ultima columna
	
	pedirDatos(boleta, mat);
	mostrarDatos(boleta, mat);
	
	return 0;
}

void pedirDatos(double boleta[MAT+1][PER], char mat[MAT][50]){
	double suma_MAT=0.0, suma_par=0.0;
	int i,j;
	char color[16];
	for(i=0; i<MAT; i++){
		sprintf(color,"color %d",i+1);
		system(color);
		printf("\nIntroduce el nombre de tu materia (%d): \t",i+1);
		gets(mat[i]); //Leemos el nombre de la materia
		fflush(stdin); //???????
		for(j=0; j<PER-1; j++){
			if(j<3) //si estamos pidiendo parciales
 				printf("\nDame la calificacion de la Materia [%d]: \t",j+1);
			else //si estamos pidiendo el ordinario
				printf("\nDame la calificacion del ordinario: \t");
			scanf("%lf",&boleta[i][j]);
			fflush(stdin);
			if(j<3) //guardamos la suma de los parciales, no del ordinario
				suma_MAT = suma_MAT + boleta[i][j];
		}
		boleta[i][4] = ((suma_MAT/3)*.5) + (boleta[i][3] *.5); //Calculamos el promedio final de cada Materia.
		suma_MAT=0; //reiniciamos el acumulados de la suma de las materias
		system("cls");
	}

	for(i=0; i<PER; i++){
		for(j=0; j<=MAT; j++){
			if(j<MAT)
				suma_par = suma_par + boleta[j][i]; //almacena la suma de los parciales
			else
				boleta[j][i] = 1.0*suma_par / MAT; //calcula el promedio por parcial
		}
		suma_par=0.0;
	}
}

void mostrarDatos(double boleta[MAT+1][PER], char mat[MAT][50]){
	int i,j;
	for(i=0; i<=MAT; i++){
		if(i==0)
			printf("MAT.\t\tP1\t P2\t P3\t Ord.\t C.F\n");
		if(i<MAT){
			printf("\n%s\t\t%.2lf \t %.2lf \t %.2lf \t %.2lf \t %.2lf",mat[i],boleta[i][0], boleta[i][1], boleta[i][2], boleta[i][3], boleta[i][4]);
		}
		else if(MAT!=1){ //solo se hara una vez
			printf("\nC.F.P\t");
			printf("\t%.2lf \t %.2lf \t %.2lf \t %.2lf \t %.2lf",boleta[i][0], boleta[i][1], boleta[i][2], boleta[i][3], boleta[i][4]);
		}
	}
}