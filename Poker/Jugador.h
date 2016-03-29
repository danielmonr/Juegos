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

#include "Carta.h"
#include <iostream>

class Jugador{
	private:
		int numero;
		int dinero;
		int fd;

	public:
		Jugador();
		Jugador(int, int);
		~Jugador();
		int pagar(int);
		int cobrar(int);
		int recibirMano(Carta, Carta);
		Carta* mano;
		int getFileDescriptor();
		int getNum();
}

#endif
