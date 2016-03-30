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
	os << " \e[1;37;42m____" << std::endl;
	os << "\e[1;37;42m|";
	int n = c.getNumero();
	if (n == 10){
		os << "\e[1;37;42m10   |" << std::endl;
	}
	else if (n == 11){
		os  << "\e[1;37;42mJ    |" << std::endl;
	}
	else if(n == 12){
		os << "\e[1;37;42mQ    |" << std::endl;
	}
	else if(n == 13){
		os << "\e[1;37;42mK    |" << std::endl;
	}
	else{
		os << n <<"\e[1;37;42m    |" << std::endl;
	}
	switch (c.getColor()){
		case 'd':
			os << "\e[1;37;42m|\e[1;31;42m\xE2\x99\xA6    \e[1;37;42m|";
			break;
		case 't':
			os << "\e[1;37;42m|\e[0;30;42m\xE2\x99\xA3    \e[1;37;42m|";
			break;
		case 's':
			os << "\e[1;37;42m|\e[0;30;42m\xE2\x99\xA0    \e[1;37;42m|";
			break;
		case 'c':
			os << "\e[1;37;42m|\e[1;31;42m\xE2\x99\xA5    \e[1;37;42m|";
			break;
	}
	os << "\n \u203e\u203e\u203e\u203e\u203e" << std::endl;
	return os;
}
