/*
 * =====================================================================================
 *
 *       Filename:  Pantalla.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/03/16 13:59:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Pantalla.h"

bool Pantalla::curses_ON = false;
WINDOW* Pantalla::dispDialog = nullptr;
WINDOW* Pantalla::playerInfo = nullptr;
WINDOW* Pantalla::playerMoney = nullptr;
char* Pantalla::buff = (char*) malloc (BUFF_SIZE);

void Pantalla::startCurses(int n){
	int x, y;
        if(curses_ON)
                refresh();
        else{
                initscr();
                cbreak();
                noecho();
                intrflush(stdscr, false);
                keypad(stdscr, true);
                atexit(endCurses);
                curses_ON = true;
				getmaxyx(stdscr, y, x);
				playerInfo = newwin(1, 10, 0,0);
				dispDialog = newwin(3,x,y-3, 0);
				playerMoney = newwin(1, 10, 0, x/2);
				intrflush(playerInfo, false);
				intrflush(dispDialog, false);
				keypad(dispDialog, true);
                refresh();
                box(dispDialog, 0,0);
				move(1,0);
                printw("Main Window");
                mvwprintw(dispDialog, 0, 0, "Alertas");
				mvwprintw(playerInfo, 0,0, "Jugador ");
				mvwprintw(playerMoney, 0, 0, "$");
                refresh();
                wrefresh(dispDialog);
				wrefresh(playerInfo);
				wmove(dispDialog, 1,1);
				wrefresh(dispDialog);
        }
}

void Pantalla::endCurses(){
        if(curses_ON && !isendwin())
                clear();
        delwin(dispDialog);
		delwin(playerInfo);
        endwin();
		//free(buff);
}

void Pantalla::print(char* s){
	wmove(stdscr, 1,0);
	refresh();
	wprintw(stdscr,s);
	refresh();
}

void Pantalla::dialog(char* s){
	wmove(dispDialog, 1, 1);
	wprintw(dispDialog, s);
	wrefresh(dispDialog);
}

void Pantalla::printInfo(Jugador* j){
	int d = j->getDinero();
	int n = j->getNum();
	mvwprintw(playerInfo, 0, 8, "%d", n);
	mvwprintw(playerMoney, 0,1, "%d", d);

	refresh();
	wrefresh(playerInfo);
	wrefresh(playerMoney);
}

void Pantalla::chat(){

}

void Pantalla::printGame(){

}

char* Pantalla::escribirDialog(){
	bool activo = true;
	int cont = 0;
	wmove(dispDialog, 1, 1);
	wrefresh(dispDialog);
	while(activo && cont < BUFF_SIZE){
		int ch = wgetch(dispDialog);
		switch(ch){
			case ESC:
				activo = false;
				break;
			case UP:
				break;
			case DOWN:
				break;
			case LEFT:
				break;
			case RIGHT:
				break;
			case BACKSPACE:
				break;
			case '\n':
				return buff;
				break;
			default:
				waddch(dispDialog, ch);
				break;
		}
	}
}
