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
		Carta* t  = new Carta('d', i);
		baraja.push_back(t);
	}
	for(int i = 1; i <= 13; ++i){
		Carta* t = new Carta('c', i);
		baraja.push_back(t);
	}
	for(int i = 1; i <= 13; ++i){
		Carta* t = new Carta('s', i);
		baraja.push_back(t);
	}
	for(int i = 1; i <= 13; ++i){
		Carta* t = new Carta('t', i);
		baraja.push_back(t);
	}
}

void Baraja::revolver(){
	srand((unsigned)time(NULL));
	std::random_shuffle(baraja.begin(), baraja.end());
}

Carta* Baraja::getCarta(){
	Carta* temp = baraja.back();
	baraja.pop_back();
	return temp;
}

std::ostream & operator << (std::ostream & os, Baraja & b){
	for (auto item:b.baraja){
		os << *item << " ";
	}
	return os;
}
