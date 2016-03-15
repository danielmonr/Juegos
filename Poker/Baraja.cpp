/*
 * =====================================================================================
 *
 *       Filename:  Baraja.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 12:04:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include "Baraja.h"

Baraja::Baraja(){
	for(int i = 1; i <= 13; ++i){
		baraja.push_back(Carta('d', i));
	}
	for(int i = 1; i <= 13; ++i){
		baraja.push_back(Carta('c', i));
	}
	for(int i = 1; i <= 13; ++i){
		baraja.push_back(Carta('s', i));
	}
	for(int i = 1; i <= 13; ++i){
		baraja.push_back(Carta('t', i));
	}
}

std::vector<Carta> Baraja::revolver(){
	std::srand(unsigned (time(0)));
	std::random_shuffle (baraja.begin(), baraja.end() );
}

std::ostream & operator << (std::ostream & os, Baraja & b){
	for (auto item:b.baraja){
		os << item << " ";
	}
	return os;
}
