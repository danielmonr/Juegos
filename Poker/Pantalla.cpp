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

void Pantalla::startCurses(){
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
				dispDialog = newwin(10,20,5,15);
                refresh();
                box(dispDialog, 0,0);
                printw("Main Window");
                mvwprintw(dispDialog, 1, 1, "subwindow");
                refresh();
                wrefresh(dispDialog);
        }
}

void Pantalla::endCurses(){
        if(curses_ON && !isendwin())
                clear();
        delwin(dispDialog);
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
