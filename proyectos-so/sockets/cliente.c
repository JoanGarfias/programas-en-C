/*Cliente que solicita sumar dos numeros enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in server_addr;
	int num[2], res;
	
	if(argc != 4){
		printf("Faltan argumentos!!\n\tUso: %s num1 num2 dirip\n",argv[0]);
		return -1;
	}
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((void *)&server_addr, sizeof(server_addr)); //Inicializa todo en cero (tipos de datos)
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[3]);
	server_addr.sin_port = htons(4200); //sirve para comunicar un sistema operativo con otro
	
	if(connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error en la llamada a connect");
		return -1;
	}
	num[0] = atoi(argv[1]);
	num[1] = atoi(argv[2]);
	write(sd, (char *) num, 2 * sizeof(int));
	read(sd, (char *)&res, sizeof(int));
	
	printf("Resultado es %d\n",res);
	
	close(sd);
	return 0;
}
