#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct persona{
    char nombre[32];
    int edad;
}PERSONA;

typedef struct nodo{
    PERSONA dato;
    struct nodo *sig;
}NODO;

typedef struct cola{
    NODO *primero;
    NODO *ultimo;
}COLA;

COLA crearCola();
int estaVacia(COLA *);
void colar(COLA *, PERSONA);
PERSONA desencolar(COLA *);
PERSONA primero(COLA *);
PERSONA ultimo(COLA *);
PERSONA pedirPaciente();
void cargarDatos(COLA *);
void guardarDatos();

COLA *reserva = NULL;

int main(){
    COLA cola = crearCola();
	reserva = &cola;
	atexit(guardarDatos);
    cargarDatos(&cola);
    PERSONA paciente;
    NODO *aux; //Para lista completa y eliminar
    int op;
    do{
        printf("\n\n__________ SISTEMA DE HOSPITALES _____________");
        printf("\n\n______ 1) Agregar paciente");
        printf("\n\n______ 2) Atender paciente");
        printf("\n\n______ 3) Ver proximo paciente");
        printf("\n\n______ 4) Ver ultimo paciente");
        printf("\n\n______ 5) Ver lista de pacientes");
        printf("\n\n______ 6) Salir\n    -->");
        fflush(stdin);
        scanf("%d", &op);
        if(op==6)
            break;
        switch(op){
        case 1:
            paciente = pedirPaciente();
            printf("\n\n(!) Se agrego exitosamente al paciente %s %d a la lista de pacientes",
                                                    paciente.nombre, paciente.edad);
            colar(&cola, paciente);
            break;
        case 2:
            if(!estaVacia(&cola)){
                paciente = desencolar(&cola);
                printf("\n\nSe atendio a: %s %d", paciente.nombre, paciente.edad);
                if(estaVacia(&cola))
                    printf("\nY fue el ultimo paciente");
                if(!estaVacia(&cola)){
                    paciente = primero(&cola);
                    printf("\n\nEl siguiente paciente a atender es: %s %d", paciente.nombre, paciente.edad);
                }
            }
            break;
        case 3:
            if(!estaVacia(&cola)){
                paciente = primero(&cola);
                printf("\n\nEl siguiente paciente a atender es: %s %d", paciente.nombre, paciente.edad);
            }
            break;
        case 4:
            if(!estaVacia(&cola)){
                paciente = ultimo(&cola);
                printf("\n\nEl ultimo paciente a atender es: %s %d", paciente.nombre, paciente.edad);
            }
            break;
        case 5:
            if(!estaVacia(&cola)){
                aux = cola.primero;
                int cont = 1;
                printf("\n\n__________ Lista de Pacientes ___________ \n\n");
                while(aux != NULL){
                    printf("%d) %s %d\n", cont, aux->dato.nombre, aux->dato.edad);
                    aux = aux->sig;
                    cont++;
                }
            }
            break;
        default:
            break;
        }
        printf("\n\n");
        system("PAUSE");
        system("CLS");
    }while(op != 6);
	
    return 0;
}

COLA crearCola(){
    COLA temp;
    temp.primero = NULL;
    temp.ultimo = NULL;
    return temp;
}

int estaVacia(COLA *cola){
    return cola->primero == NULL;
}

void colar(COLA *cola, PERSONA dato){

    NODO *aux = (NODO *) malloc(sizeof(NODO));
    aux->dato = dato;
    aux->sig = NULL;

    if(estaVacia(cola)){
        cola->primero = aux;
        cola->ultimo = aux;
    }
    else{
        cola->ultimo->sig = aux;
        cola->ultimo = aux;
    }
}

PERSONA desencolar(COLA *cola){
    PERSONA p;
    if(!estaVacia(cola)){
        p = cola->primero->dato;
        NODO *aux = cola->primero;
        cola->primero = cola->primero->sig;
        free(aux);
    }
    else{
        printf("\nLa cola ya esta vacia");
    }
    return p;
}

PERSONA primero(COLA *cola){
    PERSONA p;
    if(!estaVacia(cola)){
        p = cola->primero->dato;
    }
    else{
        printf("\nLa cola ya esta vacia");
    }
    return p;
}


PERSONA ultimo(COLA *cola){
    PERSONA p;
    if(!estaVacia(cola)){
        p = cola->ultimo->dato;
    }
    else{
        printf("\nLa cola ya esta vacia");
    }
    return p;
}

PERSONA pedirPaciente(){
    PERSONA temp;
    fflush(stdin);
    printf("\n\nIntroduzca el nombre del paciente: \n--> ");
    fgets(temp.nombre, 32, stdin);
    temp.nombre[strlen(temp.nombre) -1] = '\0';
    printf("\n\nIntroduzca la edad del paciente: \n--> ");
    scanf("%d", &temp.edad);
    return temp;
}

void cargarDatos(COLA *cola){
    FILE *db = fopen("pacientes.txt", "r");
    if(db == NULL){
        fclose(db);
        return;
    }
    PERSONA p; //paciente
    int i = 0;
    char aux;
    while( (fscanf(db, "%d ", &p.edad) ) != EOF){
        while( ((aux = fgetc(db)) != '\n') && aux != EOF){
            p.nombre[i] = aux;
            i++;
        }
        p.nombre[i] = '\0';
        i=0;
        colar(cola, p);
		p.nombre[0] = '\0';
    }
    fclose(db);
    return;
}

void guardarDatos(){
    FILE *db = fopen("pacientes.txt", "w+");
    if(db == NULL){
        fclose(db);
        return;
    }
    PERSONA p; //paciente
    while(!estaVacia(reserva)){
        p = desencolar(reserva);
        if( (fprintf(db, "%d %s", p.edad, p.nombre) ) != EOF )
            fprintf(db, "\n");
    }
    printf("\n\nDatos guardados exitosamente...");
    fclose(db);
    return;
}
