//* Crear un archivo de texto (.txt) donde guardar los emails de amigos

//? fprintf(puntero,informacion);
//? fwrite(datoAGuardar,Tamaño,Longitud,puntero);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fd;

struct datosUsuarios{
    char nombre[30];
    char apellidos[30];
    char email[40];
}datos;


int main() {

    char direccion[] = "FWRITEEJ2.txt";
    char rpt;
    fd = fopen(direccion,"at");

    if (fd == NULL){
        printf("Error al tratar de crear el archivo\n");
        return 1;
    }
    printf("\t***AGENDA DE EMAILS***");
    fprintf(fd,"\t***AGENDA DE EMAIL***");

    do{
        fflush(stdin);
        printf("\n Nombre: ");gets(datos.nombre);
        printf("\n Apellidos: ");gets(datos.apellidos);
        printf("\n Email: ");gets(datos.email);

        fprintf(fd,"\n\nNombre: ");
        fwrite(datos.nombre,1,strlen(datos.nombre),fd);
        fprintf(fd,"\nApellidos: ");
        fwrite(datos.apellidos,1,strlen(datos.apellidos),fd);
        fprintf(fd,"\nEmail: ");
        fwrite(datos.email,1,strlen(datos.email),fd);
        printf("\n");
        printf("Desea Agregar mas contactos (s): \n");
        scanf("%c",&rpt);

    } while (rpt == 's');

    return 0;
}
