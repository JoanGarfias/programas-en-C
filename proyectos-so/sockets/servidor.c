/*servidor para sumar dos numeros enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void)
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sd, sc, size, num[2], res; //Los sockets son enteros, por facilidad
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((void *)&server_addr, sizeof (server_addr));
	
	/*Configurar el socket*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; //Cualquier dirección de entrada
	server_addr.sin_port = htons(4200);
	
	//Vamos a publicarlo, le decimos al SO que estamos creando un socket
	/*Debemos asegurarnos que no esté ocupado*/
	bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	//Este listen limita a que solo sean 5 peticiones por cada ciclo de reloj
	listen(sd, 5);
	size = sizeof(client_addr);

	while(1){
		printf("esperando conexión\n");
		sc = accept(sd, (struct sockaddr *)&client_addr, &size); //Esto devuelve si el cliente se pudo conectar
		if(sc < 0)
			break;
			
		/*Lo que viene después en la practica no se hace de forma secuencial,
		 * sino que todo se ejecuta levantando un hilo, esto para atender varias peticiones al mismo tiempo.
		 * */
			
		read(sc, (char *) num, 2 * sizeof(int));
		printf("Sumando %d + %d\n",num[0], num[1]);
		res = num[0] + num[1];
		write(sc, (char *)&res, sizeof(int));
		close(sc);
		printf("Listo!!\n");		
	}
	
	perror("Error en accept");
	close(sd);
	
	return 0;
}
