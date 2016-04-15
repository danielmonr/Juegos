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
int j_repartir, turno, grande;
Jugador** mesa;
Baraja* baraja;
vector<Carta*> c_mesa;
char buff_in[BUFF_SIZE];
int bin_size;

// Funciones el juego
void Jugar();
void Ronda();
void Setup();
typedef void (* rondas_t)(int, int, int);
rondas_t *rondas;
void r1(int, int, int);
void r2(int, int, int);
void r3(int, int, int);
void r4(int, int, int);

// Funciones auxiliares
int transformToInt();
void send_message_player(int, char*);
void send_message_all(char*);
void send_number_all(int);
void receive_message_player(int);

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


	/*  Arreglo de funciones para las rondas */
	rondas = (rondas_t*) malloc (4*  sizeof(rondas_t));
	*rondas = r1;
	*(rondas+1) = r2;
	*(rondas+2) = r3;
	*(rondas+3) = r4;

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

	free(baraja);
	free(mesa);
	free(rondas);
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
	j_repartir = 0;
	cout << "Setup completo" << endl;
	free(buffer);
}

void Jugar(){
	char* buffer = (char*) malloc (BUFF_SIZE* sizeof(char));
	int pot = 0;
	j_repartir = 0;
	c_mesa.empty();
	cout << "Nueva Mano" << endl;
	baraja = new Baraja();
	baraja->revolver();
	cout << "Repartir cartas..." << endl;
	for(int i = 0; i < num_jugadores; ++i){
		mesa[i]->recibirMano(baraja->getCarta(), baraja->getCarta());
		sprintf(buffer, "/j%d/%c%d/%c%d", mesa[i]->getNum(), mesa[i]->getMano().first->getColor(), mesa[i]->getMano().first->getNumero(), mesa[i]->getMano().second->getColor(), mesa[i]->getMano().second->getNumero());
		send_message_player(i, buffer);
	}

	Ronda();
	free(buffer);
}

void Ronda(){
	char* buffer = (char*) malloc(BUFF_SIZE*sizeof(char));
	int apuesta = d_inicial / 100;
	int j_max;
	vector<Carta*> cartas_m;
	int pot = 0;
	int current_bet = 0;
	int newbet = 0;
	int j_grande, j_chica, turno;
	bool terminado = true;
	j_grande = j_repartir -2;
	j_chica = j_repartir -1;
	if(j_grande < 0)
		j_grande = num_jugadores + j_grande;
	if(j_chica < 0)
		j_chica = num_jugadores + j_chica;
	j_max = j_grande;
	turno = j_grande - 1;
	if (turno < 0)
		turno = num_jugadores + turno;

	bool jugando = true, ronda_apuestas;
	// Mensaje de comienzo
	sprintf(buffer, "/e");
	send_message_all(buffer);

	// Mensaje de posicion del dealer
	sprintf(buffer, "/d%d", j_repartir+1);
	send_message_all(buffer);
	// Mensaje de la ciega grande
	sprintf(buffer, "/g%d/%d", j_grande+1, apuesta);
	send_message_all(buffer);
	// Esperar a que el jugador pague
	receive_message_player(j_grande);
	while(buff_in[1] == 'E' && mesa[j_grande]->getDinero() >= apuesta){
		send_message_player(j_grande, buffer);
		receive_message_player(j_grande);
	}
	// asignar el pago y actualizar el pot
	mesa[j_grande]->pagar(apuesta);
	pot += apuesta;
	sprintf(buffer, "/p%d", pot);
	send_message_all(buffer);

	// Mensaje de ciega chica
	sprintf(buffer, "/c%d/%d", j_chica+1, apuesta/2);
	send_message_all(buffer);
	receive_message_player(j_chica);
	while(buff_in[1] == 'E' && mesa[j_chica]->getDinero() >= apuesta){
		send_message_player(j_chica, buffer);
		receive_message_player(j_chica);
	}
	mesa[j_chica]->pagar(apuesta/2);
	pot += apuesta/2;
	sprintf(buffer, "p/%d", pot);
	send_message_all(buffer);
	// Fin proceso ciega chica

	ronda_apuestas = true;
	for(int rt = 0; rt < 4; rt++){
		// Enviar mensaje de comienzo de una ronda: /r(num ronda)
		sprintf(buffer, "/r%d", rt);
		send_message_all(buffer);
		terminado = true;
		rondas[rt](turno, j_max, apuesta);
		while(turno != j_max){
			if(!mesa[turno]->getActivo())
				continue;
			else
				terminado = false;
			sprintf(buffer, "/t%d", turno+1);
			receive_message_player(turno);
			switch(buff_in[1]){
				case 'E':
					break;
				case 'i':
					current_bet = mesa[turno]->getPot();
					mesa[turno]->pagar(apuesta-current_bet);
					pot += apuesta-current_bet;
					// Enviar respuesta de jugador a todos
					sprintf(buffer, "/i%d", turno+1);
					send_message_all(buffer);
					// Enviar mensaje de actualizacion de pot a todos
					sprintf(buffer, "/p%d", pot);
					send_message_all(buffer);
					break;
				case 's':
					current_bet = mesa[turno]->getPot();
					newbet = transformToInt();
					mesa[turno]->pagar(newbet-current_bet);
					pot += apuesta-current_bet;
					// Enviar respuesta de jugador a todos
					sprintf(buffer,"/s%d/%d", turno, newbet);
					send_message_all(buffer);
					apuesta = newbet;
					j_max = turno;
					// Enviar mensaje de actualizacion de pot
					sprintf(buffer, "/p%d", pot);
					send_message_all(buffer);
					break;
				case 'f':
					mesa[turno]->desactivar();
					sprintf(buffer, "/f%d", turno+1);
					break;
			}
			turno--;
			if(turno < 0)
				turno = num_jugadores -1;
		}
		if(terminado){
			printf("Se acabo el juego todos foldearon.\n");
			sprintf("/w%d", j_max);
			return;
		}
	}

	free(buffer);
}

void levantarse(int n){
	free(mesa[n-1]);
	mesa[n-1] = nullptr;
}

void r1(int turno, int j_max, int apuesta){
	printf("Ronda de apuestas uno.\nTurno de %d, apuesta de: %d, jugador grande: %d\n", turno, apuesta, j_max);
}

void r2(int turno, int j_max, int apuesta){
	printf("Ronda de apuestas dos.\nTurno de %d, apuesta de: %d, jugador grande: %d\n", turno, apuesta, j_max);
	char* buffer = (char*) malloc (BUFF_SIZE);
	// Destapar 3 cartas
	int i;
	Carta* c;
	sprintf(buffer,"/a%d", 3);
	for (i = 0; i < 3; ++i){
		c = baraja->getCarta();
		c_mesa.push_back(c);
		sprintf(buffer+strlen(buffer), "/%c%d", c->getColor, c->getNumero());
	}
	send_message_all(buffer);
	free(buffer);
}

void r3(int turno, int j_max, int apuesta){
	printf("Ronda de apuestas tres.\nTurno de %d, apuesta de: %d, jugador grande: %d\n", turno, apuesta, j_max);
	char* buffer = (cahr*) malloc (BUFF_SIZE);
	Carta* c;
	c = baraja->getCarta();
	c_mesa.push_back(c);
	sprintf(buffer, "/a%d", 4);
	for (auto item:c_mesa){
		sprintf(buffer+strlen(buffer), "/%c%d", item->getColor(), item->getNumero());
	}
	send_message_all(buffer);
	free(buffer);
}

void r4(int turno, int j_max, int apuesta){
	printf("Ronda de apuestas cuatro.\nTurno de %d, apuesta de: %d, jugador grande: %d\n", turno, apuesta, j_max);
	char* buffer = (cahr*) malloc (BUFF_SIZE);
	Carta* c;
	c = baraja->getCarta();
	c_mesa.push_back(c);
	sprintf(buffer, "/a%d", 5);
	for (auto item:c_mesa){
		sprintf(buffer+strlen(buffer), "/%c%d", item->getColor(), item->getNumero());
	}
	send_message_all(buffer);
	free(buffer);
}


// ================================================ Funciones auxiliares ==================================

int transformToInt(){
	int i, temp = 0;
	for (i = 2; i < strlen(buff_in); ++i){
		temp *= 10;
		temp += buff_in[i] -'0';
	}
	return temp;
}

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

void receive_message_player(int p){
	if(mesa[p]){
		bin_size = read(mesa[p]->getFileDescriptor(), buff_in, sizeof(buff_in)-1);
		buff_in[bin_size] = '\0';
	}
}
