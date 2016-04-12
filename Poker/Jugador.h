/*
 * =====================================================================================
 *
 *       Filename:  Jugador.h
 *
 *    Description:  Cabezera de la clase Jugador.
 *
 *        Version:  1.0
 *        Created:  15/03/16 13:53:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __Poker__Jugador__
#define __Poker__jugador__

#pragma once

#include "Carta.h"
#include <iostream>

class Jugador{
	private:
		int numero;
		int dinero;
		int fd;
		std::pair<Carta*, Carta*> mano;

	public:
		Jugador();
		Jugador(int, int);
		~Jugador();
		int pagar(int);
		int cobrar(int);
		int recibirMano(Carta*, Carta*);	
		int getFileDescriptor();
		int getNum();
		int getDinero();
		std::pair<Carta*, Carta*> getMano();
};

#endif
