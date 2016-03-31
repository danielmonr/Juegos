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
                refresh();
                box(dispDialog, 0,0);
				move(1,0);
                printw("Main Window");
                mvwprintw(dispDialog, 0, 0, "Alertas");
				mvwprintw(playerInfo, 0,0, "Jugador %d", n);
                refresh();
                wrefresh(dispDialog);
				wrefresh(playerInfo);
        }
}

void Pantalla::endCurses(){
        if(curses_ON && !isendwin())
                clear();
        delwin(dispDialog);
		delwin(playerInfo);
        endwin();
}

void Pantalla::print(std::string s){

}

void Pantalla::dialog(std::string s){

}

void Pantalla::chat(){

}

void Pantalla::printGame(){

}
