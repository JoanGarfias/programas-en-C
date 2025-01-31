#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct elemento {
    double x; // Numerador
    double n; // Potencia
} ELEM;

typedef struct expresion {
    ELEM *elem;
    int cant; // Cantidad de elementos
} EXP;

typedef struct matriz {
    EXP **exp;
    int n;
} MATRIZ;

MATRIZ crearMatriz(int n);
void generarLambda(MATRIZ *mat);
void imprimirMatriz(MATRIZ mat);
EXP calcularDeterminante(MATRIZ mat);
EXP evaluar(EXP e1, EXP e2);
EXP generarPolinomio(MATRIZ mat);
EXP restar(EXP e1, EXP e2);
EXP sumar(EXP a, EXP b);


void invertir_polinomio(EXP *polinomio);
EXP reducirPolinomio(EXP polinomio);

void solucionarPolinomio(EXP polinomio);

int main() {
    int n,i;
    double epsilon = 1e-6;
    int max_iter = 100;


    printf("\nIngrese la dimension de la matriz cuadrada: \n--> ");
    scanf("%d", &n);

    MATRIZ mat = crearMatriz(n);

    generarLambda(&mat);

    imprimirMatriz(mat);

    EXP polinomio = reducirPolinomio(generarPolinomio(mat));

    printf("\nPolinomio resultante:\n");
    for(i = 0; i < polinomio.cant; i++) {
        printf("%.0lfx^%.0lf ", polinomio.elem[i].x, polinomio.elem[i].n);
    }

    printf("\nPolinomio ordenado: ");
    invertir_polinomio(&polinomio);
    for(i = 0; i < polinomio.cant; i++) {
        printf("%.0lfx^%.0lf ", polinomio.elem[i].x, polinomio.elem[i].n);
    }

    printf("\n");
    solucionarPolinomio(polinomio);

    return 0;
}

MATRIZ crearMatriz(int n) {
    MATRIZ nuevo;
    int i, j;

    nuevo.n = n;
    nuevo.exp = (EXP **) calloc(n, sizeof(EXP *));
    for(i = 0; i < n; i++) {
        nuevo.exp[i] = (EXP *) calloc(n, sizeof(EXP));
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            nuevo.exp[i][j].elem = (ELEM *) calloc(1, sizeof(ELEM));
            printf("MATRIZ [%d, %d] = ", i, j);
            scanf("%lf", &(nuevo.exp[i][j].elem[0].x));
            nuevo.exp[i][j].elem[0].n = 0;
            nuevo.exp[i][j].cant = 1;
        }
    }

    return nuevo;
}

void imprimirMatriz(MATRIZ mat) {
    int i, j, k;
    for(i = 0; i < mat.n; i++) {
        printf("[ ");
        for(j = 0; j < mat.n; j++) {
            printf("| ");
            for(k = 0; k < mat.exp[i][j].cant; k++) {
                printf("(%lf,%lf)", mat.exp[i][j].elem[k].x, mat.exp[i][j].elem[k].n);
            }
            printf(" |");
        }
        printf(" ]");
        printf("\n");
    }
}

void generarLambda(MATRIZ *mat) {
    int i, j;

    for(i = 0; i < mat->n; i++) {
        for(j = 0; j < mat->n; j++) {
            if(i == j) {
                mat->exp[i][j].elem = (ELEM *) realloc(mat->exp[i][j].elem, sizeof(ELEM) * 2);
                mat->exp[i][j].elem[1].x = -1;
                mat->exp[i][j].elem[1].n = 1;
                mat->exp[i][j].cant = 2;
            }
        }
    }
}

EXP calcularDeterminante(MATRIZ mat) {
    if (mat.n == 1) {
        return mat.exp[0][0];
    }

    if (mat.n == 2) {
        EXP a = evaluar(mat.exp[0][0], mat.exp[1][1]);
        EXP b = evaluar(mat.exp[0][1], mat.exp[1][0]);
        return restar(a, b);
    }

    EXP det;
    det.cant = 1;
    det.elem = (ELEM*) malloc(sizeof(ELEM));
    det.elem[0].x = 0;
    det.elem[0].n = 0;

    int signo = 1;
    int i, j, k;

    for (k = 0; k < mat.n; k++) {
        MATRIZ submatriz;
        submatriz.n = mat.n - 1;
        submatriz.exp = (EXP**) malloc((submatriz.n) * sizeof(EXP*));

        for (i = 0; i < submatriz.n; i++) {
            submatriz.exp[i] = (EXP*) malloc((submatriz.n) * sizeof(EXP));
            for (j = 0; j < submatriz.n; j++) {
                submatriz.exp[i][j] = mat.exp[i + 1][(j >= k) ? j + 1 : j];
            }
        }

        EXP subdet = calcularDeterminante(submatriz);
        EXP producto = evaluar(mat.exp[0][k], subdet);

        for (i = 0; i < producto.cant; i++) {
            producto.elem[i].x *= signo;
        }

        EXP temp = sumar(det, producto);
        det = temp;

        signo = -signo;

        for (i = 0; i < submatriz.n; i++) {
            free(submatriz.exp[i]);
        }
        free(submatriz.exp);
    }

    return det;
}


EXP evaluar(EXP e1, EXP e2) {
    EXP nueva = (EXP) { .elem = NULL, .cant = 0 };
    int i,j;

    for(i = 0; i < e1.cant; i++) {
        for(j = 0; j < e2.cant; j++) {
            nueva.cant++;
            nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
            nueva.elem[nueva.cant - 1].x = e1.elem[i].x * e2.elem[j].x;
            nueva.elem[nueva.cant - 1].n = e1.elem[i].n + e2.elem[j].n;
        }
    }

    printf("\n\n");
    for(i=0; i<e1.cant; i++){
        printf("[%lf, %lf] ", e1.elem[i].x, e2.elem[i].n);
    }
    printf(" * ");
    for(i=0; i<e2.cant; i++){
        printf("[%lf, %lf] ", e2.elem[i].x, e2.elem[i].n);
    }
    printf(" = ");
    for(i=0; i<nueva.cant; i++){
        printf("[%lf, %lf] ", nueva.elem[i].x, nueva.elem[i].n);
    }

    return nueva;
}

EXP generarPolinomio(MATRIZ mat) {
    return calcularDeterminante(mat);
}

EXP restar(EXP e1, EXP e2) {
    EXP nueva = (EXP) { .elem = NULL, .cant = 0 };

    int i = 0, j = 0;

    while (i < e1.cant && j < e2.cant) {
        if (e1.elem[i].n == e2.elem[j].n) {
            int coeficiente = e1.elem[i].x - e2.elem[j].x;
            int potencia = e1.elem[i].n;

            if (coeficiente != 0) {
                nueva.cant++;
                nueva.elem = (ELEM *)realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
                nueva.elem[nueva.cant - 1].x = coeficiente;
                nueva.elem[nueva.cant - 1].n = potencia;
            }

            i++;
            j++;
        } else if (e1.elem[i].n < e2.elem[j].n) {
            nueva.cant++;
            nueva.elem = (ELEM *)realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
            nueva.elem[nueva.cant - 1].x = e1.elem[i].x;
            nueva.elem[nueva.cant - 1].n = e1.elem[i].n;

            i++;
        } else {
            nueva.cant++;
            nueva.elem = (ELEM *)realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
            nueva.elem[nueva.cant - 1].x = -e2.elem[j].x;
            nueva.elem[nueva.cant - 1].n = e2.elem[j].n;

            j++;
        }
    }

    // Agregar los elementos restantes de e1
    while (i < e1.cant) {
        nueva.cant++;
        nueva.elem = (ELEM *)realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
        nueva.elem[nueva.cant - 1].x = e1.elem[i].x;
        nueva.elem[nueva.cant - 1].n = e1.elem[i].n;

        i++;
    }

    // Agregar los elementos restantes de e2
    while (j < e2.cant) {
        nueva.cant++;
        nueva.elem = (ELEM *)realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
        nueva.elem[nueva.cant - 1].x = -e2.elem[j].x;
        nueva.elem[nueva.cant - 1].n = e2.elem[j].n;

        j++;
    }

    return nueva;
}

EXP reducirPolinomio(EXP polinomio) {
    EXP reducido = (EXP) { .elem = NULL, .cant = 0 };

    for (int i = 0; i < polinomio.cant; i++) {
        double coeficiente = polinomio.elem[i].x;
        double potencia = polinomio.elem[i].n;

        // Verificar si el término ya existe en el polinomio reducido
        int encontrado = 0;
        for (int j = 0; j < reducido.cant; j++) {
            if (reducido.elem[j].n == potencia) {
                reducido.elem[j].x += coeficiente;
                encontrado = 1;
                break;
            }
        }

        // Si no se encuentra, agregar el término al polinomio reducido
        if (!encontrado) {
            reducido.cant++;
            reducido.elem = (ELEM *)realloc(reducido.elem, sizeof(ELEM) * reducido.cant);
            reducido.elem[reducido.cant - 1].x = coeficiente;
            reducido.elem[reducido.cant - 1].n = potencia;
        }
    }

    return reducido;
}

EXP sumar(EXP a, EXP b) {
    EXP nueva = (EXP) { .elem = NULL, .cant = 0 };

    int i = 0, j = 0;

    while (i < a.cant && j < b.cant) {
        if (a.elem[i].n == b.elem[j].n) {
            int coeficiente = a.elem[i].x + b.elem[j].x;
            int potencia = a.elem[i].n;

            if (coeficiente != 0) {
                nueva.cant++;
                nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
                nueva.elem[nueva.cant - 1].x = coeficiente;
                nueva.elem[nueva.cant - 1].n = potencia;
            }

            i++;
            j++;
        } else if (a.elem[i].n < b.elem[j].n) {
            nueva.cant++;
            nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
            nueva.elem[nueva.cant - 1].x = a.elem[i].x;
            nueva.elem[nueva.cant - 1].n = a.elem[i].n;

            i++;
        } else {
            nueva.cant++;
            nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
            nueva.elem[nueva.cant - 1].x = b.elem[j].x;
            nueva.elem[nueva.cant - 1].n = b.elem[j].n;

            j++;
        }
    }

    // Agregar los elementos restantes de a
    while (i < a.cant) {
        nueva.cant++;
        nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
        nueva.elem[nueva.cant - 1].x = a.elem[i].x;
        nueva.elem[nueva.cant - 1].n = a.elem[i].n;

        i++;
    }

    // Agregar los elementos restantes de b
    while (j < b.cant) {
        nueva.cant++;
        nueva.elem = (ELEM *) realloc(nueva.elem, sizeof(ELEM) * nueva.cant);
        nueva.elem[nueva.cant - 1].x = b.elem[j].x;
        nueva.elem[nueva.cant - 1].n = b.elem[j].n;

        j++;
    }

    return nueva;
}
void invertir_polinomio(EXP *polinomio) {
    int i = 0;
    int j = polinomio->cant - 1;

    while (i < j) {
        ELEM temp = polinomio->elem[i];
        polinomio->elem[i] = polinomio->elem[j];
        polinomio->elem[j] = temp;

        i++;
        j--;
    }
}

void solucionarPolinomio(EXP polinomio){
    int i, grado = polinomio.cant;
    int pivote = polinomio.elem[polinomio.cant - 1].x;

    int divs = 2;
    int *divisores = (int *) calloc(divs, sizeof(int));
    divisores[0]=1;
    divisores[1]=-1;

    if(pivote != 1 && pivote != 0){
        divs+=2;
        divisores = (int *) realloc((void*)divisores, sizeof(int) * 1 * divs);
        divisores[2]= pivote;
        divisores[3]= -pivote;
    }

    int *raices = (int *) calloc(grado, sizeof(int));

    for(i=2; i<=pivote/2; i++){
        if(i % pivote == 0){
            divs+=2;
            divisores[divs-2] = i;
            divisores[divs-1] = -i;
        }
    }

    long int r = 0;
    int j, cont = 0;

    for(i=0; i<divs; i++){
        for(j=0; j<polinomio.cant; j++){
            r+= polinomio.elem[j].x * (int) pow(divisores[i], polinomio.elem[j].n);
        }
        if(r == 0){
            printf("\n\nSolucion %d: %d", cont+1, divisores[i]);
            cont++;
        }
        r = 0;
    }

}
