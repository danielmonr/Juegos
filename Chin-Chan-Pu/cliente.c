/*
 * =====================================================================================
 *
 *       Filename:  socket_cliente.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/02/16 11:11:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define TCP_PORT 8000

int cliente;

void cerrar(int);

int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char buffer, res;
	int gano;
    
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);
    
    // Establecer conexión
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
	signal(SIGINT, cerrar);

    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Comunicación
    
    if (estado == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
		
        // Leer de teclado y escribir en socket
        while (leidos = read(fileno(stdin), &buffer, sizeof(char))) {
			printf("Escogiste %c\n", buffer);
			read(cliente, &res, sizeof(char));
			printf("Escogio %c\n", res);
            write(cliente, &buffer, leidos);
			read(cliente, &gano, sizeof(int));



			if(gano == 1){
				printf("Perdiste :C\n");
			}
			else if(gano == 0)
				printf("Ganaste! :D\n");
			else
				printf("EMPATE :|\n");
        }
    }
    
    // Cerrar el socket
    close(cliente);
    
    return 0;
}

void cerrar(int sig){
	close(cliente);
	exit(0);
}
