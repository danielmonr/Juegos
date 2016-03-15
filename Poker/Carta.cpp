/*
 * =====================================================================================
 *
 *       Filename:  Carta.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 11:55:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Carta.h"

Carta::Carta(){
	std::cout<< "Creando carta..." << std::endl;
	std::cout << "Color (d,s,c o t): ";
	std::cin >> color;
	numero = 0;
	while(numero < 1 || numero > 13){
		std::cout << "Numero (entre 1 y 13): ";
		std::cin >> numero;
	}
}

Carta::Carta(char c, int n){
	color = c;
	numero = n;
}

char Carta::getColor(){
	return color;
}

int Carta::getNumero(){
	return numero;
}

std::ostream & operator << (std::ostream & os, Carta & c){
	os << " ____" << std::endl;
	os << "|";
	int n = c.getNumero();
	if (n == 10){
		os << "10   |" << std::endl;
	}
	else if (n == 11){
		os  << "J    |" << std::endl;
	}
	else if(n == 12){
		os << "Q    |" << std::endl;
	}
	else if(n == 13){
		os << "K    |" << std::endl;
	}
	else{
		os << n <<"    |" << std::endl;
	}
	switch (c.getColor()){
		case 'd':
			os << "|\xE2\x99\xA6    |";
			break;
		case 't':
			os << "|\xE2\x99\xA3    |";
			break;
		case 's':
			os << "|\xE2\x99\xA0    |";
			break;
		case 'c':
			os << "|\xE2\x99\xA5    |";
			break;
	}
	os << "\n \u203e\u203e\u203e\u203e\u203e" << std::endl;
	return os;
}
