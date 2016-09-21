/*
 * =====================================================================================
 *
 *       Filename:  cliente.cpp
 *
 *    Description:  Cliente para el juego de Poker
 *
 *        Version:  1.0
 *        Created:  08/03/16 20:11:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include 	<iostream>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    <pthread.h>
#include    <stdlib.h>
#include    <string.h>
#include 	<curses.h>
#include    "semaphore.h"
#include    <queue>

using namespace std;

pthread_mutex_t mutex;
sem_t cambios;
pthread_t lectura, escritura;

#define TCP_PORT 8002
#define BUFF_SIZE 250

bool curses_ON = false;

int caracteres;
queue<int>states;
int state = 0;
int cliente;

// funciones para el manejo de comunicacion
void* receiveMsg(void* args);
void* sendMsg(void* args);
int msgToState(char*);
int stateHandler();
char* traducir(char* txt);

void signalHandler(int s);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	/*if(argc != 2){
		cout << "Error en el numero de argumentos. porfavor ingrese un ip valida.\n";
		abort();
	}*/

	char buffer[BUFF_SIZE];
	struct sockaddr_in direccion;

	cliente = socket(PF_INET, SOCK_STREAM, 0);

	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton("127.0.0.7", &direccion.sin_addr);

	int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));

	if (estado == 0) {
		cout << "Conectado a " << inet_ntoa(direccion.sin_addr) << ":" << ntohs(direccion.sin_port) << endl;
		//caracteres = read(cliente, &buffer, BUFF_SIZE);
		//string str(buffer);
		//cout<< "Recibi: " << str << std::endl;
		//int esc = read(fileno(stdin), &buffer, BUFF_SIZE);
		//write(cliente, &buffer, esc);
		//write(fileno(stdout), &buffer, caracteres);
		//cout << "\n";
		signal(SIGINT, signalHandler);
		sem_init(&cambios, 0, 0);
		pthread_create(&lectura, NULL, receiveMsg, (void*)&cliente);
		pthread_create(&escritura, NULL, sendMsg, (void*)&cliente);

		while(true){
			sem_wait(&cambios);
			pthread_mutex_lock(&mutex);

		}

		pthread_join(lectura,NULL);
		pthread_join(escritura, NULL);
	}
	else {
		cout << "Fallo en la coneccion.\n";
		close(cliente);
		return EXIT_SUCCESS;
	}

	//sleep(3);

	close(cliente);
	

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* receiveMsg(void* args){
	char* buffer = (char*) malloc (BUFF_SIZE);
	int temp;
	int _cliente = *((int*) args);
	while(read(_cliente, buffer, BUFF_SIZE)){
		string str(buffer);
		temp = msgToState(buffer);
		cout << "Recibido: " << str << " -> Senal: " << temp << endl;
		pthread_mutex_lock(&mutex);
		states.push(temp);
		pthread_mutex_unlock(&mutex);
		sem_post(&cambios);
	}
}

void* sendMsg(void* args){
	int _cliente = *((int*) args);
	char* buffer = (char*) malloc (BUFF_SIZE);	
	while(read(fileno(stdin), buffer, sizeof(buffer))){
		char* answer = traducir(buffer);
		write(_cliente, answer, sizeof(answer));
	}
}

char* traducir(char* txt){
	return "first";
}

int msgToState(char* msg){
	char temp = *msg;
	switch(temp){
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
	}
}

void signalHandler(int s){
	cout << "Terminando juego...\n";
	pthread_cancel(lectura);
	pthread_cancel(escritura);
	wait(lectura);
	wait(escritura);
	cout << "Cerrando coneccion...\n";
	close(cliente);
	signal(SIGINT, SIG_DFL);
	raise(SIGINT);
}

/*
void Pantalla(){
	startCurses();
}

void imprimirInfo(){
	int row, col;
	row = col = 0;
	move(row, col);

}

void startCurses(){
	if(curses_ON){
		refresh();
	}
	else{
		initscr();
		cbreak();
		noecho();
		intrflush(stdscr, false);
		keypad(std, true);
		atexit(endCurses);
		curses_ON = true;
	}
}

void endCurses(){
	if(curses_ON && !isendwin()){
		curses_ON = false;
		clear();
		endwin();
	}
}
*/