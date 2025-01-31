#include<stdio.h>
#include<stdlib.h>

#define MAX 30
#define MAXSTR 32

typedef struct persona{
    int numero;
    char nombre[MAXSTR];
}PERSONA;

void eliminar(PERSONA *, PERSONA);
int buscar(PERSONA *, PERSONA);
void insertar(PERSONA *, PERSONA);
int funcionHash(PERSONA);
void mostrar(PERSONA *);
PERSONA pedirDatos();
int contDigs(int);

int main(){
    PERSONA tabla[MAX];
    int i;

    for(i=0; i<MAX; i++)
        tabla[i] = (PERSONA) {-1, "null"};
    mostrar(tabla);
    insertar(tabla, pedirDatos() );

    mostrar(tabla);
    return 0;
}

int funcionHash(PERSONA dato){
    return dato.numero % MAX;
}

void insertar(PERSONA *tabla, PERSONA dato){
    int pos = funcionHash(dato);
    tabla[pos] = dato;
}

void mostrar(PERSONA *tabla){
    int i;
    for(i=0; i<MAX; i++)
        printf("T_hash[%d]: %d | %s\n",i, tabla[i].numero, tabla[i].nombre);
    printf("\n\n");
}

void eliminar(PERSONA *tabla, PERSONA dato){
    int pos = funcionHash(dato);
    if(dato.numero == tabla[pos].numero){
        tabla[pos] = (PERSONA) {-1, "null"};
    }
    else{
        printf("\n\nEl dato no existe");
    }
    return;
}

int buscar(PERSONA *tabla, PERSONA dato){
    int pos = funcionHash(dato);
    if(tabla[pos].numero == dato.numero){
        printf("\n\nEl dato %d esta en la posicion %d de la tablaHash", dato, pos);
        return pos;
    }
    else{
        printf("\n\nEl dato no existe en la tabla");
        return -1;
    }
}

PERSONA pedirDatos(){
    PERSONA p;
    fflush(stdin);
    do{
        printf("\n\nIntroduzca el digito: ");
        scanf("%d", &p.numero);
    }while(contDigs(p.numero) > 2);
    printf("\n\nIntroduzca el nombre: ");
    scanf("%s", p.nombre);
    return p;
}

int contDigs(int n){
    if(n<10) return 1;
    return 1 + contDigs(n/10);
}
