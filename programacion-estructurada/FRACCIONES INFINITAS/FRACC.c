#include<stdio.h>
#include<stdlib.h>
struct fraccion{
	int num;
	int den;	
};
typedef struct fraccion FRACC;

FRACC sumarFracc(FRACC *, FRACC *);
void mostrarFracc(FRACC);
FRACC calcularFracciones(FRACC *, int);
void pedirDatos(FRACC *);
int mcd(int, int);

int main(){
	FRACC * listaFR = NULL;
	char opcion = 's';
	int i = 1;
	do{
		listaFR = (FRACC *) realloc(listaFR, sizeof(FRACC) * i);
		pedirDatos(listaFR+i-1);
		if(i>=2){
			do{
				printf("\nDesea seguir agregando mas fracciones? Escriba \t(s/n)");
				fflush(stdin);
				scanf("%c",&opcion);
			}while(opcion!='s' && opcion!='n');
		}
		i++;
	}while(opcion=='s');
	FRACC result = calcularFracciones(listaFR, i-1);
	printf("\n\t---- RESULTADO -----\n");
	mostrarFracc(result);
	printf("\n\n");
	system("pause");
	free(listaFR);
	return 0;
}

void mostrarFracc(FRACC fracc){
	if(fracc.num != fracc.den && fracc.den!=1){
		printf("\n\t\t  %d\n\t\t-----\n",fracc.num);
		printf("\t\t  %d",fracc.den);	
	}
	else{
		printf("\n\t\t %d",fracc.num);
	}
}

int mcd(int a, int b){
	return (b==0)? a : mcd(b,a%b);
}

void pedirDatos(FRACC *fracc){
		printf("\nIntroduzca el numerador: \t ");
		scanf(" %d",&fracc->num);
		printf("\nIntroduzca el denominador: \t ");
		scanf(" %d",&fracc->den);
}

FRACC sumarFracc(FRACC *f1, FRACC *f2){
	FRACC sum;
	int mcdtemp;
	if(&f1->den == &f2->den){
		sum.num = * &f1->num +  * &f2->num;
		sum.den = * &f1->den; //o f2.den
	}
	else{
		sum.num = ((* &f1->num) * (* &f2->den) ) + ( (* &f1->den) * (* &f2->num) );
		sum.den = (* &f1->den) * ( * &f2->den);
	}
	mcdtemp = mcd(sum.num, sum.den);
	if(mcdtemp!=1){
		sum.num = sum.num / mcdtemp;
		sum.den = sum.den / mcdtemp;
	}
	return sum;
}

FRACC calcularFracciones(FRACC *listaFR, int tams){
	int i;
	for(i=tams; i>1; i--){
		*(listaFR+i-2) = sumarFracc(listaFR+i-1,listaFR+i-2);
	}
	return *listaFR;
}