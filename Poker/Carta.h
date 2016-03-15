/*
 * =====================================================================================
 *
 *       Filename:  Carta.h
 *
 *    Description:  Cabezera para la clase Carta, vease Baraja para su implementacion.
 *
 *        Version:  1.0
 *        Created:  15/03/16 11:49:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __Poker__Carta__
#define __Poker__Carta__

#include <iostream>

class Carta{
	private:
		char color;
		int numero;
	public:
		Carta();
		Carta(char, int);
		int getNumero();
		char getColor();

		friend std::ostream & operator << (std::ostream & os, Carta & c);
};

#endif
