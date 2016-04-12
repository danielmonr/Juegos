/*
 * =====================================================================================
 *
 *       Filename:  Baraja.h
 *
 *    Description:  Cabezera de la clase Baraja, implementa la clase Carta.
 *
 *        Version:  1.0
 *        Created:  15/03/16 12:00:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef __Poker__Baraja__
#define __Poker__Baraja__

#include "Carta.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "time.h"

class Baraja{
	private:
		std::vector<Carta*> baraja;
	public:
		Baraja();
		void revolver();
		Carta* getCarta();

		friend std::ostream & operator <<(std::ostream&, Baraja & b);
};

#endif
