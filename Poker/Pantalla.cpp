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
WINDOW* Pantalla::pot = nullptr;
WINDOW* Pantalla::mesa = nullptr;
WINDOW* Pantalla::mano = nullptr;
char* Pantalla::buff = (char*) malloc (BUFF_SIZE);

void Pantalla::startCurses(int n){
	int x, y;
        if(curses_ON)
                refresh();
        else{
				setlocale(LC_ALL, "en_US.utf-8");
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
				mano = newwin(y-6, x/5, 2, 0);
				mesa = newwin(y-6, 4*x/5, 2, 1+(x/5));
				intrflush(playerInfo, false);
				intrflush(dispDialog, false);
				keypad(dispDialog, true);
                refresh();
                box(dispDialog, 0,0);
				box(mano, 0,0);
				box(mesa, 0,0);
				move(1,0);
                printw("Main Window");
				const char clubs[] = {static_cast<char>(0xE2), static_cast<char>(0x99),static_cast<char>(0xA3), static_cast<char>(0)};
				printw("%s", clubs);
                mvwprintw(dispDialog, 0, 0, "Alertas");
				mvwprintw(playerInfo, 0,0, "Jugador ");
				mvwprintw(playerMoney, 0, 0, "$");
                refresh();
                wrefresh(dispDialog);
				wrefresh(playerInfo);
				wrefresh(mesa);
				wrefresh(mano);
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

void Pantalla::printGame(std::vector<Carta*> m, int pot_m){
	int x, y, size_pot;
	size_pot = 0;
	int temp = pot_m;
	while(temp > 1){
		size_pot++;
		temp /= 10;
	}
	size_pot += 6;
	getmaxyx(mesa,y,x);
	wmove(mesa, 1,(x/2)-(size_pot/2));
	wprintw(mesa, "pot = %d", pot_m);

	int x_cont = 3;
	for(auto item:m){
		//mvwprintw(mesa, 2, x_cont, item->getRepre());
		printCard(item, mesa, x_cont, 2);
		x_cont += 6;
	}

	refresh();
	wrefresh(mesa);
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

void Pantalla::printCard(Carta* c, WINDOW* win, int x, int y){
	//mvwprintw(win, y,x, "\u250c\u2500\u2500\u2500\u2500\u2510");
	mvwaddstr(win, y, x , c->getRepre().c_str());
	wrefresh(win);
}
