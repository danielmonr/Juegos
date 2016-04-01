/*
 * =====================================================================================
 *
 *       Filename:  Jugador.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 14:00:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Jugador.h"

Jugador::Jugador(){
	std::cout << "Jugador vacio\n";
}

Jugador::Jugador(int n, int f){
	numero = n;
	fd = f;
	dinero = 5000;
}

Jugador::~Jugador(){
	free(mano);
}

int Jugador::pagar(int n){
	if(n <= dinero){
		dinero -= n;
		return n;
	}
	else
		return 0;
}

int Jugador::cobrar(int n){
	dinero +=n;
	return dinero;
}

int Jugador::recibirMano(Carta u, Carta d){
	if(mano != nullptr){
		mano = (Carta*) malloc (2 * sizeof(Carta));
		*mano = u;
		*(mano+1) = d;
		return 1;
	}
	else
		return -1;
}

int Jugador::getFileDescriptor(){
	return fd;
}

int Jugador::getNum(){
	return numero;
}

int Jugador::getDinero(){
	return dinero;
}
