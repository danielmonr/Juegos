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

void Baraja::revolver(){
	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(baraja), std::end(baraja), engine);
}

Carta Baraja::getCarta(){
	Carta temp = baraja.back();
	baraja.pop_back();
	return temp;
}

std::ostream & operator << (std::ostream & os, Baraja & b){
	for (auto item:b.baraja){
		os << item << " ";
	}
	return os;
}
