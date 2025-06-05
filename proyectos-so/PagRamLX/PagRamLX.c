
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOQUE_MB 10
#define NUM_ITERACIONES 5

void mostrar_memoria() {
    FILE *fp = fopen("/proc/self/status", "r");
    if (!fp) {
        perror("No se pudo abrir /proc/self/status");
        return;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), fp)) {
        if (strncmp(linea, "VmSize:", 7) == 0 ||
            strncmp(linea, "VmRSS:", 6) == 0 ||
            strncmp(linea, "VmSwap:", 7) == 0) {
            printf("%s", linea);
        }
    }

    fclose(fp);
}

int main() {
    printf("=== Observando crecimiento de memoria con malloc ===\n");

    void *bloques[NUM_ITERACIONES] = {0};

    for (int i = 0; i < NUM_ITERACIONES; i++) {
        size_t tamanio = BLOQUE_MB * 1024 * 1024;
        bloques[i] = malloc(tamanio);

        if (!bloques[i]) {
            fprintf(stderr, "Fallo malloc en iteración %d\n", i);
            break;
        }

        // Tocar la memoria para asegurar que se asigna físicamente
        memset(bloques[i], 1, tamanio);

        printf("\nIteración %d: +%d MB\n", i + 1, BLOQUE_MB);
        mostrar_memoria();

        sleep(1);
    }

    printf("\nFinalizando. Liberando memoria...\n");
    for (int i = 0; i < NUM_ITERACIONES; i++) {
        free(bloques[i]);
    }
    mostrar_memoria();

    return 0;
}
