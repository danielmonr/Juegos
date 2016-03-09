/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  Juego de poker, programa del sevidor. Debe aceptar hasta 5 jugadores.
 *
 *        Version:  1.0
 *        Created:  08/03/16 13:10:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */



#include	<iostream>
#include    <unistd.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>

#define TCP_PORT 8001
// numero de conecciones posibles
#define N 5

using namespace std;

int servidor, cliente;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	if (argc < 2){
		cout << "Error porfavor ingrese un dirección ip.\nAbortando...\n";
		abort();
	}
	if (argc > 2){
		cout << "Numero de argumentos no válidos.\nAbortando\n";
	}

	pid_t* pid = (pid_t) malloc (N * sizeof(pid_t));
	int cont = 0;

	/*  Mensajes de entrada */
	cout << "############## Bienvenido a POKER ITC. #############" << endl;
	cout << "######### Desarrollado por: Daniel Monzalvo ########" << endl;

	/*  Inicio del servidor */
	struct sockaddr_in direccion;
	char buffer[1000];

	//crear el servidor
	servidor = socket(PF_INET, SOCK_STREAM, 0);

	//establecer coneccion con el servidor
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton(argv[1], &direccion.sin_addr);
	bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));

	// escuchar clientes
	listen(servidor, N);

	socklen_t tam = sizeof(direccion);
	while(1){
		cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
		cout << "Aceptando conexiones en "<< inet_ntoa(direccion.sin_addr) << ":" << ntohs(direccion.sin_port) << endl;
		*(pid+(cont++)) = fork();
		if(paid == 0) break;	
	}
	if(*(pid+cont) == 0){
		close(servidor);
		close(cliente);
	}
	else if(*(pid+cont)== 0){

	}

	free(pid);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
