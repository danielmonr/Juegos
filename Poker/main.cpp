/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 12:42:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <iostream>
#include    <unistd.h>
#include    <stdio.h>
#include    "Baraja.h"
#include    "Pantalla.h"

#define SIZE_BUFFER 256

char* buffer;
char* escribir();

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Baraja *b = new Baraja();
	b->revolver();
	Pantalla::startCurses(2);
	//Pantalla::print("hola");
	escribir();

	Pantalla::endCurses();
	

	/*initscr();
	printw("Main window");
	WINDOW* sb = newwin(10,20,5,15);
	refresh();
	box(sb, 0, 0);
	mvwprintw(sb,1,1, "subwindow");
	refresh();
	wrefresh(sb);
	getch();
	delwin(sb);
	endwin(); */

	buffer = (char*) malloc (SIZE_BUFFER);
	escribir();
	free(buffer);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

char* escribir(){
	bool activo = true;
	int cont = 0;
	while (activo && cont < SIZE_BUFFER){
		int ch = wgetch(Pantalla::dispDialog);
		switch(ch){
			case 27:
				activo = false;
				break;
			case '\n':
				return buffer;
				break;
			default:
				waddch(Pantalla::dispDialog, ch);
				break;
		}
	}
}
