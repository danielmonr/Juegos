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
#include    <pthread.h>
#include    <stdlib.h>
#include    "Baraja.h"
#include    "Jugador.h"

#define TCP_PORT 8001
// numero de conecciones posibles, maximo de jugadores
#define N 10

using namespace std;

int servidor, cliente;
static unsigned cli_count = 0;
Jugador* mesa[N];


void* manejar_jugador(void*);
void levantarse(int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pthread_t con_mngr;

	if (argc < 2){
		cout << "Error porfavor ingrese un dirección ip.\nAbortando...\n";
		abort();
	}
	if (argc > 2){
		cout << "Numero de argumentos no válidos.\nAbortando\n";
	}


	/*  Mensajes de entrada */
	cout << "############## Bienvenido a POKER ITC. #############" << endl;
	cout << "######### Desarrollado por: Daniel Monzalvo ########" << endl;

	/*  Inicio del servidor */
	struct sockaddr_in direccion;
	struct sockaddr_in cli_addr;

	//crear el servidor
	servidor = socket(PF_INET, SOCK_STREAM, 0);

	// Ligar socket con una direccion y puerto
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton(argv[1], &direccion.sin_addr);
	bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));

	// escuchar clientes
	listen(servidor, N);

	socklen_t tam = sizeof(direccion);
	
	while(1){
		cliente = accept(servidor, (struct sockaddr *) &cli_addr, &tam);

		if((cli_count+1) == N){
			cout << "Número maximo de conecciones alcanzada.\n" << "Rechazar: " << inet_ntoa(cli_addr.sin_addr) << endl;
			close(cliente);
			continue;
		}

		cout << "Aceptando conexiones en "<< inet_ntoa(direccion.sin_addr) << ":" << ntohs(direccion.sin_port) << endl;
		int num = 0, i;
		// Buscar el lugar en la mesa disponile
		for(i = 0; i < N; +i){
			if(!mesa[i]){
				num = i;
				break;
			}
		}
		Jugador* j = new Jugador(num+1, cliente);
		mesa[num] = j;
		pthread_create(&con_mngr, NULL, &manejar_jugador, (void*)j);
		sleep(1);
	}

	close(servidor);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

// Maneja las comunicaciones con el jugador
void* manejar_jugador(void* arg){
	Jugador* j = (Jugador*) arg;
	close(j->getFileDescriptor());
	levantarse(j->getNum());
}

void Jugar(){
	int pot = 0;
	cout << "Nueva Mano" << endl;
	Baraja* baraja = new Baraja();
	baraja->revolver();
	
}

void levantarse(int n){
	free(mesa[n-1]);
	mesa[n-1] = nullptr;
}
