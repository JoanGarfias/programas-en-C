/*servidor para sumar dos numeros enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

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

void *atender(void *arg){
    int sc = *(int *)arg;
    free(arg);

    int num[2], res;

    if(recv_all(sc, (char *) num, 2 * sizeof(int)) == 2 * sizeof(int)) {
        res = num[0] + num[1];
        if (send_all(sc, (char *)&res, sizeof(int)) <= 0) {
            perror("Error enviando respuesta, no soy whatsapp brother");
        }
    } else {
        perror("Error leyendo datos del cliente, como chingaesewe");
    }

    close(sc);
    return NULL;
}

int main(void)
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sd;
	socklen_t size;
	int opt = 1;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("Error en socket");
		return 1;
	}

	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror("Error en setsockopt, ni idea que es pero suena cool");
		close(sd);
		return 1;
	}

	bzero((void *)&server_addr, sizeof (server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(4200);
	if (bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Error en bind");
		close(sd);
		return 1;
	}

	if (listen(sd, 5) < 0) {
		perror("Error en listen");
		close(sd);
		return 1;
	}

	while(1){
		printf("esperando conexión\n");
		size = sizeof(client_addr);
		int sc = accept(sd, (struct sockaddr *)&client_addr, &size);
		if(sc < 0) {
			perror("Error en accept, fallaste en fallar");
			continue;
		}

		pthread_t th;
		int *psc = malloc(sizeof(int));
		if (psc == NULL) {
			perror("Error en malloc");
			close(sc);
			continue;
		}
		*psc = sc;
		if (pthread_create(&th, NULL, atender, (void *)psc) != 0) {
			perror("Error en pthread_create karnal");
			close(sc);
			free(psc);
			continue;
		}
		if (pthread_detach(th) != 0) {
			perror("Error en pthread_detach mejor cambiate de carrera");
		}

	}
	close(sd);

	return 0;
}
