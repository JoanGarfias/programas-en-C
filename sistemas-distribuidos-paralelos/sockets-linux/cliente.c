/*Cliente que solicita sumar dos numeros enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static ssize_t recv_all(int fd, void *buf, size_t len)
{
	size_t total = 0;
	char *ptr = (char *)buf;

	while (total < len) {
		ssize_t n = read(fd, ptr + total, len - total);
		if (n <= 0) return n;
		total += (size_t)n;
	}
	return (ssize_t)total;
}

static ssize_t send_all(int fd, const void *buf, size_t len)
{
	size_t total = 0;
	const char *ptr = (const char *)buf;

	while (total < len) {
		ssize_t n = write(fd, ptr + total, len - total);
		if (n <= 0) return n;
		total += (size_t)n;
	}
	return (ssize_t)total;
}

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in server_addr;
	int num[2], res = 0;
	
	if(argc != 4){
		printf("Faltan argumentos!!\n\tUso: %s num1 num2 dirip\n",argv[0]);
		return -1;
	}
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((void *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[3]);
	server_addr.sin_port = htons(4200);
	
	if(connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error en la llamada a connect");
		return -1;
	}
	num[0] = atoi(argv[1]);
	num[1] = atoi(argv[2]);
	if (send_all(sd, (char *)num, 2 * sizeof(int)) <= 0) {
		perror("Error enviando datos");
		close(sd);
		return -1;
	}
	if (recv_all(sd, (char *)&res, sizeof(int)) <= 0) {
		perror("Error leyendo respuesta");
		close(sd);
		return -1;
	}
	
	printf("Resultado es %d\n",res);
	
	close(sd);
	return 0;
}
