#include "automatas.h"

int main() {
    char nombreAutomata[50];
    printf("Ingrese el nombre del automata: ");
    scanf("%s", nombreAutomata);

    char crearCarpeta[100];
    sprintf(crearCarpeta, "mkdir %s", nombreAutomata);
    system(crearCarpeta);

    char rutaDirectorio[100];
    sprintf(rutaDirectorio, "./%s/", nombreAutomata); // Ruta al directorio

    AUTOMATA automata = crearAutomata();

    int numEstados, numAlfabeto, numEstadosFinales;
    printf("Ingrese el numero de estados: ");
    scanf("%d", &numEstados);

    printf("Ingrese los estados (separados por espacio): ");
    getchar(); // Limpiar el buffer del salto de linea anterior
    char estadosInput[100];
    fgets(estadosInput, sizeof(estadosInput), stdin);
    char *token = strtok(estadosInput, " ");
    while (token != NULL) {
        agregarListaChar(&automata.estados, token[0]);
        token = strtok(NULL, " ");
    }

    printf("Ingrese el numero de simbolos del alfabeto: ");
    scanf("%d", &numAlfabeto);

    printf("Ingrese el alfabeto (separados por espacio): ");
    getchar(); // Limpiar el buffer del salto de linea anterior
    char alfabetoInput[100];
    fgets(alfabetoInput, sizeof(alfabetoInput), stdin);
    token = strtok(alfabetoInput, " ");
    while (token != NULL) {
        agregarListaChar(&automata.alfabeto, token[0]);
        token = strtok(NULL, " ");
    }

    printf("Ingrese el estado inicial: ");
    scanf(" %c", &automata.estadoInicial);

    printf("Ingrese el numero de estados finales: ");
    scanf("%d", &numEstadosFinales);

    printf("Ingrese los estados finales (separados por espacio): ");
    getchar(); // Limpiar el buffer del salto de linea anterior
    char estadosFinalesInput[100];
    fgets(estadosFinalesInput, sizeof(estadosFinalesInput), stdin);
    token = strtok(estadosFinalesInput, " ");
    while (token != NULL) {
        agregarListaChar(&automata.estadosFinales, token[0]);
        token = strtok(NULL, " ");
    }

    sprintf(rutaDirectorio, "./%s/", nombreAutomata);
    FILE *archivoEstados = fopen(strcat(rutaDirectorio, "estados.txt"), "w");
    if (archivoEstados == NULL) {
        printf("Error al abrir el archivo estados.txt\n");
        return 1;
    }
    for (int i = 0; i < automata.estados.tam; i++) {
        fprintf(archivoEstados, "%c\n", automata.estados.lista[i]);
    }
    fclose(archivoEstados);

    sprintf(rutaDirectorio, "./%s/", nombreAutomata);
    FILE *archivoAlfabeto = fopen(strcat(rutaDirectorio, "alfabeto.txt"), "w");
    if (archivoAlfabeto == NULL) {
        printf("Error al abrir el archivo alfabeto.txt\n");
        return 1;
    }
    for (int i = 0; i < automata.alfabeto.tam; i++) {
        fprintf(archivoAlfabeto, "%c\n", automata.alfabeto.lista[i]);
    }
    fclose(archivoAlfabeto);

    sprintf(rutaDirectorio, "./%s/", nombreAutomata);
    FILE *archivoEstadoInicial = fopen(strcat(rutaDirectorio, "estadoInicial.txt"), "w");
    if (archivoEstadoInicial == NULL) {
        printf("Error al abrir el archivo estadoInicial.txt\n");
        return 1;
    }
    fprintf(archivoEstadoInicial, "%c", automata.estadoInicial);
    fclose(archivoEstadoInicial);

    sprintf(rutaDirectorio, "./%s/", nombreAutomata);
    FILE *archivoEstadosFinales = fopen(strcat(rutaDirectorio, "estadosFinales.txt"), "w");
    if (archivoEstadosFinales == NULL) {
        printf("Error al abrir el archivo estadosFinales.txt\n");
        return 1;
    }
    for (int i = 0; i < automata.estadosFinales.tam; i++) {
        fprintf(archivoEstadosFinales, "%c\n", automata.estadosFinales.lista[i]);
    }
    fclose(archivoEstadosFinales);

    printf("Automata '%s' creado exitosamente.\n", nombreAutomata);
    printf("(!) LAS FUNCIONES DE TRANSICION NO FUERON AGREGADAS");

    return 0;
}
