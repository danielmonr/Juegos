/*
 * =====================================================================================
 *
 *       Filename:  Juego.h
 *
 *    Description:  Juego de poker, programa del sevidor. Debe aceptar hasta 5 jugadores.
 *					Manejador de partidas.
 *
 *        Version:  1.0
 *        Created:  22/08/16 16:44:28
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __Poker__Juego__
#define __Poker__Juego__

#include    <unistd.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    <pthread.h>
#include    <stdlib.h>
#include    <string.h>
#include    <vector>
#include    <queue>
#include    "Jugador.h"

#define BUFF_SIZE 150
#define N 10

class Juego{
	private:
		// Puerto asignado
		int TCP_PORT;
		// Dinero sobre la mesa
		int pot;
		// Número de jugadores conectados
		int j_conectados;
		// ID de la sala
		int id;

		// Funciones para el manejo de los sockets
		static void* buscarJugadores(void*);
		int manejarConeccionesActivas();

		// Funciones para el manejo de Jugadores
		int quitarJugador(int);
		
		// Funciones para la funcionalidad de la partida
		int iniciarPartida();
		int terminarPartida();
		int Repartir();
		int destapar();
		int desechar();
		int pagar();
		int asignarRoles();
		int rondaApuestas();
		int rondaUno();

		// Manejo de mensajes
		int enviarMensajeJugador();
		int enviarMensajeTodos(char*);
		int recivirMensajeJugador(int);
		int transformarAInt();

		// Que jugador abrió la sala
		Jugador* anfitrion;
		// Jugadores en la mesa
		std::vector<Jugador*> jugadores;
		// Jugadores en espera
		std::queue<Jugador*> espera;

		// variables para conectividad
		char* ip;
		struct sockaddr_in direccion;
		struct sockaddr_in cli_addr;
		socklen_t tam;
		int servidor, cliente;
		char buff_in[BUFF_SIZE];
		int bin_size;
		pthread_t nuevas_conec;

	public:
		// Funciones de inicializacion de partida
		Juego();
		Juego(int tcp_port, int i);
		int crearSocket();

		// Destructor de partida
		~Juego();

		//Funciones de manejo de variables
		int getId();

};

#endif
