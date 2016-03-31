/*
 * =====================================================================================
 *
 *       Filename:  Pantalla.h
 *
 *    Description:  Archivo para Curses, manejador de la pantalla.
 *
 *        Version:  1.0
 *        Created:  31/03/16 10:48:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __Poker_Pantalla
#define __Poker_Pantalla

#pragma once

#include <iostream>
#include <curses.h>
#include "Jugador.h"

#define ESC 27
#define UP 259
#define DOWN 258
#define LEFT 260
#define RIGHT 261
#define BACKSPACE 127
#define BUFF_SIZE 256

class Pantalla{
	private:
		static WINDOW* playerInfo;
		static WINDOW* dispDialog;
		static WINDOW* playerMoney;
		static WINDOW* pot;
		static WINDOW* mesa;
		static WINDOW* mano;
		static char* buff;
	public:
		static bool curses_ON;
		static void startCurses(int);
		static void endCurses();

		static void print(char *);
		static void dialog(char*);
		static void chat();
		static void printGame();
		static void printInfo(Jugador*);

		static char* escribirDialog();
};

#endif
