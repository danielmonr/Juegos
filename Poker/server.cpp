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
#include    <string.h>
#include    "Baraja.h"
#include    "Jugador.h"

#define TCP_PORT 8001
// numero de conecciones posibles, maximo de jugadores
#define N 10
#define BUFF_SIZE 150

using namespace std;

// Variables Globales
int servidor, cliente;
int num_jugadores, d_inicial;
int repartir, turno, grande;
Jugador** mesa;
vector<Carta*> c_mesa;

// Funciones el juego
void Jugar();
void Ronda();
void Setup();

// Funciones auxiliares
void send_message_player(int, char*);
void send_message_all(char*);
void send_number_all(int);

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

	// Inicializar la barrera y la variable del tamano del socket
	socklen_t tam = sizeof(direccion);
	//pthread_barrier_init(&barrera, NULL, N);

	// Preguntar cuantos clientes
	cout << "Cuantos jugadores?" << endl;
	cin >> num_jugadores;

	// Preguntar el dinero inicial
	cin >> d_inicial;

	// Crear arreglo de jugadores
	mesa = (Jugador**) malloc (num_jugadores * sizeof(Jugador*));
	
	// Esperar num_jugadores para jugar
	for (int i = 0; i < num_jugadores; ++i){
		cliente = accept(servidor, (struct sockaddr *) &cli_addr, &tam);

		cout << "Aceptando conexiones en "<< inet_ntoa(direccion.sin_addr) << ":" << ntohs(direccion.sin_port) << endl;
		// Crear al jugador con su numero y su filedescriptor
		Jugador* j = new Jugador(i+1, cliente);
		// Añadir al jugador al arreglo
		*(mesa+i) = j;
	}



	// Empezar el juego
	Setup();
	Jugar();


	free(mesa);
	close(servidor);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*  ====================================== Funciones del Juego =========================================== */

void Setup(){
	char* buffer = (char*) malloc (BUFF_SIZE * sizeof(char)); // Crear buffer para la funcion
	cout << "Iniciando juego..." << endl;
	cout << "Enviando informacion a jugadores (numero, dinero inicial)." << endl;
	for (int i = 0; i < num_jugadores; ++i){ // Loop para asignar dinero inicial a jugadores y enviar informacion de numero y dinero inicial a cada jugador
		sprintf(buffer, "/s/%d/%d", mesa[i]->getNum(), mesa[i]->cobrar(d_inicial));
		send_message_player(i, buffer);
	}
	cout << "Setup completo" << endl;
	free(buffer);
}

void Jugar(){
	char* buffer = (char*) malloc (BUFF_SIZE* sizeof(char));
	int pot = 0;
	repartir = 0;
	c_mesa.empty();
	cout << "Nueva Mano" << endl;
	Baraja* baraja = new Baraja();
	baraja->revolver();
	cout << "Repartir cartas..." << endl;
	for(int i = 0; i < num_jugadores; ++i){
		mesa[i]->recibirMano(baraja->getCarta(), baraja->getCarta());
		sprintf(buffer, "/j%d/%c%d/%c%d", mesa[i]->getNum(), mesa[i]->getMano().first->getColor(), mesa[i]->getMano().first->getNumero(), mesa[i]->getMano().second->getColor(), mesa[i]->getMano().second->getNumero());
		send_message_player(i, buffer);
	}
	
}

void Ronda(){

}

void levantarse(int n){
	free(mesa[n-1]);
	mesa[n-1] = nullptr;
}

// ================================================ Funciones auxiliares ==================================

void send_message_player(int p, char* s){
	if (mesa[p]){
		write(mesa[p]->getFileDescriptor(), s, strlen(s));
	}
}

void send_message_all(char* s){
	for(int i = 0; i < num_jugadores; ++i){
		if(mesa[i]){
			write(mesa[i]->getFileDescriptor(), s, strlen(s)); 
		}
	}
}

void send_number_all(int n){
	int i;
	for (i = 0; i < num_jugadores;++i){
		if(mesa[i])
			write(mesa[i]->getFileDescriptor(), &n, sizeof(int));
	}
}

