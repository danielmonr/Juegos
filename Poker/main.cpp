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

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Baraja *b = new Baraja();
	b->revolver();
	Pantalla::startCurses(2);
	Pantalla::curses_ON = false;
	
	sleep(3);

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
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
