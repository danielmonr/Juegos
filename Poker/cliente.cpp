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

#include <iostream>
#include <curses.h>


using namespace std;

#define TCP_PORT 8001

bool curses_ON = false;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	if(argc != 2){
		cout << "Error en el numero de argumentos. porfavor ingrese un ip valida.\n";
		abort();
	}

	struct sockaddr_in direccion;
	int cliente;

	cliente = socket(PF_INET, SOCK_STREAM, 0);

	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton(argv[1], &direccion.sin_addr);

	int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));

	if (estado == 0) {
		cout << "Conectado a " << inet_ntoa(direccion.sin_addr) << ":" << ntohs(direccion.sin_port) << endl;
	}

	close(cliente);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

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
