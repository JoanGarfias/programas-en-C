#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listachar{
	char *lista;
	int tam;
}LISTACHAR;

typedef struct listaint{
	int *lista;
	int tam;
}LISTAINT;

typedef struct funcion{
	char estado;
	char simbolo;
	char resultado;
}FUNCION;

typedef struct funciones{
	FUNCION *funcion;
	int tam;
}FUNCIONES;
typedef FUNCIONES LISTAFUNCIONES;

typedef struct automata{
	LISTACHAR estados;
	LISTACHAR alfabeto;
	LISTAFUNCIONES funciones;
	char estadoInicial;
	LISTACHAR estadosFinales;
}AUTOMATA;

AUTOMATA crearAutomata(){
	AUTOMATA a;
	a.alfabeto.lista = NULL;
	a.alfabeto.tam = 0;
	a.estadoInicial = '\0';
	a.estados.lista = NULL;
	a.estados.tam = 0;
	a.estadosFinales.lista = NULL;
	a.estadosFinales.tam = 0;
	a.funciones.tam = 0;
	a.funciones.funcion = NULL;
	return a;
}

LISTACHAR crearListaChar(int n){
	LISTACHAR nueva;
	nueva.lista = (char *) calloc(n, sizeof(char));
	nueva.tam = n;
	return nueva;
}

LISTAINT crearListaInt(int n){
	LISTAINT nueva;
	nueva.lista = (int *) calloc(n, sizeof(int));
	nueva.tam = n;
	return nueva;
}

FUNCION crearFuncion(char estado, char simbolo, char estadoFinal){
	FUNCION func;
	func.estado = estado;
	func.simbolo = simbolo;
	func.resultado = estadoFinal;
	return func;
}
LISTAFUNCIONES crearListaFunciones(int n){
	LISTAFUNCIONES func;
	func.funcion = (FUNCION*) calloc(n, sizeof(FUNCION));
	func.tam = n;
	return func;
}

void agregarListaChar(LISTACHAR *listaChar, char agregar) {
    listaChar->lista = (char *) realloc(listaChar->lista, sizeof(char) * 1 * (listaChar->tam + 1));
    if (listaChar->lista == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    listaChar->lista[listaChar->tam] = agregar;
    listaChar->tam = listaChar->tam + 1;
}

void agregarListaInt(LISTAINT *listaInt, int agregar) {
    listaInt->lista = (int *) realloc(listaInt->lista, sizeof(int) * 1 * (listaInt->tam + 1));
    if (listaInt->lista == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    listaInt->lista[listaInt->tam] = agregar;
    listaInt->tam = listaInt->tam + 1;
}

void agregarFuncion(LISTAFUNCIONES *listafunc, FUNCION func){
	listafunc->funcion = (FUNCION *) realloc(listafunc->funcion, sizeof(FUNCION) * (listafunc->tam+1));
	listafunc->funcion[listafunc->tam].estado = func.estado;
	listafunc->funcion[listafunc->tam].simbolo = func.simbolo;
	listafunc->funcion[listafunc->tam].resultado = func.resultado;
	listafunc->tam++;
}

char * limpiarCadena(char *cad){
	int i,tam=strlen(cad);
	for(i=0; i<tam; i++)
		cad[i] = '\0';
	return cad;
}

void imprimirAutomata(AUTOMATA a){
	int i;
	printf("\nQ = { ");
	for(i=0; i<a.estados.tam; i++){
		printf("%c ", a.estados.lista[i]);
	}
	printf("}\nA = { ");
	for(i=0; i<a.alfabeto.tam; i++){
		printf("%c ", a.alfabeto.lista[i]);
	}
	printf("}\nI = { %c }", a.estadoInicial);
	printf("\nF = { ");
	for(i=0; i<a.estadosFinales.tam; i++){
		printf("%c ", a.estadosFinales.lista[i]);
	}
	printf("}\nFunciones de Transicion: \n");
	for(i=0; i<a.funciones.tam; i++){
		printf("(%c, %c) = %c\n", a.funciones.funcion[i].estado,
								a.funciones.funcion[i].simbolo,
								a.funciones.funcion[i].resultado);
	}
}

int esEstadoFinal(AUTOMATA atf, char estado){
	int i;
	for(i=0; i<atf.estadosFinales.tam; i++)
		if(atf.estadosFinales.lista[i] == estado) return 1;
	return 0;
}

char *obtenerNuevaCadena(char *cad, int indice){
    int i,j=0;
    char *nuevaCad = (char *) calloc(strlen(cad)-indice+1, sizeof(char));
    for(i=indice; i<strlen(cad); i++, j++){
        nuevaCad[j] = cad[i];
    }
    return nuevaCad;
}

LISTAFUNCIONES obtenerListaFuncion(AUTOMATA atf, char evento, char estado){
	LISTAFUNCIONES listaFunciones;
	int i;
	listaFunciones.tam = 0;
	listaFunciones.funcion = NULL;
	
	for(i=0; i<atf.funciones.tam; i++){
		if(atf.funciones.funcion[i].estado == estado && atf.funciones.funcion[i].simbolo == evento){
			agregarFuncion(&listaFunciones, (FUNCION) {estado, evento, atf.funciones.funcion[i].resultado} );
		}
	}
	return listaFunciones;
}

LISTAINT procesarCadena(AUTOMATA atf, char *palabra, int iteracion, char estado) {
    LISTAINT resultados;
    resultados.lista = NULL;
    resultados.tam = 0;

    if (iteracion == strlen(palabra)) {
        if (esEstadoFinal(atf, estado)) {
            agregarListaInt(&resultados, 1);
            printf("Cadena aceptada\n");
        } else {
            agregarListaInt(&resultados, 0);
            printf("Cadena no aceptada\n");
        }
        return resultados;
    } else {
        printf("Estado actual: %c, Leyendo: %c\n", estado, palabra[iteracion]);
        
        LISTAFUNCIONES funcionDeTransicion = obtenerListaFuncion(atf, palabra[iteracion], estado);
        int i;
        for (i = 0; i < funcionDeTransicion.tam; i++) {
            char evento = funcionDeTransicion.funcion[i].simbolo;
            char siguienteEstado = funcionDeTransicion.funcion[i].resultado;
            
            printf("Transicion: (%c, %c) -> %c\n", estado, evento, siguienteEstado);

            LISTAINT nuevosResultados = procesarCadena(atf, palabra, iteracion + 1, siguienteEstado);
            for (int j = 0; j < nuevosResultados.tam; j++) {
                agregarListaInt(&resultados, nuevosResultados.lista[j]);
            }
        }
        return resultados;
    }
}


AUTOMATA cargarAutomata(char *ruta) {
    AUTOMATA atf;
    atf = crearAutomata();
    char leido, est, simb, res;
    char *aux = (char *) calloc(100, sizeof(char));  //Almacenar ruta completa
    // Cargando estados
    FILE *archivoEstados = fopen(strcat(strcpy(aux, ruta), "/estados.txt"), "r");
    if (archivoEstados == NULL) {
        perror("Error al abrir el archivo estados.txt");
        exit(EXIT_FAILURE);
    }
    while (fscanf(archivoEstados, "%c", &leido) != EOF) {
    	if(leido != '\n')
        agregarListaChar(&atf.estados, leido);
    }

    fclose(archivoEstados);


    sprintf(aux, "%s", ruta);

    FILE *archivoAlfabeto = fopen(strcat(aux, "/alfabeto.txt"), "r");
    if (archivoAlfabeto == NULL) {
        perror("Error al abrir el archivo alfabeto.txt");
        exit(EXIT_FAILURE);
    }

    while (fscanf(archivoAlfabeto, "%c", &leido) == 1) {
    	if(leido != '\n')
        agregarListaChar(&atf.alfabeto, leido);
    }
    fclose(archivoAlfabeto);

    sprintf(aux, "%s", ruta);
    FILE *archivoEstadosFinales = fopen(strcat(aux, "/estadosFinales.txt"), "r");
    if (archivoEstadosFinales == NULL) {
        perror("Error al abrir el archivo estadosFinales.txt");
        exit(EXIT_FAILURE);
    }

    while (fscanf(archivoEstadosFinales, "%c", &leido) == 1) {
    	if(leido != '\n')
        	agregarListaChar(&atf.estadosFinales, leido);
    }

    fclose(archivoEstadosFinales);

	sprintf(aux, "%s", ruta);

    FILE *archivoEstadoInicial = fopen(strcat(strcpy(aux, ruta), "/estadoInicial.txt"), "r");
    if (archivoEstadoInicial == NULL) {
        perror("Error al abrir el archivo estadoInicial.txt");
        exit(EXIT_FAILURE);
    }

    if (fscanf(archivoEstadoInicial, "%c", &leido) != 1) {
        perror("Error al leer el estado inicial");
        exit(EXIT_FAILURE);
    }

    atf.estadoInicial = leido;
    fclose(archivoEstadoInicial);

    sprintf(aux, "%s", ruta);
    FILE *archivoFunciones = fopen(strcat(strcpy(aux, ruta), "/funciones.txt"), "r");
    if (archivoFunciones == NULL) {
        perror("Error al abrir el archivo funciones.txt");
        exit(EXIT_FAILURE);
    }

    while (fscanf(archivoFunciones, "%c %c %c\n", &est, &simb, &res) == 3) {
        FUNCION nuevaFuncion;
        nuevaFuncion.estado = est;
        nuevaFuncion.simbolo = simb;
        nuevaFuncion.resultado = res;

        agregarFuncion(&(atf.funciones), nuevaFuncion);
    }
    fclose(archivoFunciones);
    return atf;
}

int valorEnListaInt(LISTAINT list, int valor){
	int i;
	for(i=0; i<list.tam; i++){
		if(list.lista[i]==valor)
			return 1;
	}
	return 0;
}