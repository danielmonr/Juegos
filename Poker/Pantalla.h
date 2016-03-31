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

class Pantalla{
	private:
		static WINDOW* dispDialog;
		static WINDOW* playerInfo;
	public:
		static bool curses_ON;
		static void startCurses();
		static void endCurses();

		static void print(std::string s);
		static void dialog(std::string s);
		static void chat();
		static void printGame();
};

#endif
