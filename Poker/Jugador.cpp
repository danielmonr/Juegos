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
	activo = true;
	fd = f;
	dinero = 0;
	pot = 0;
}

Jugador::~Jugador(){
	std::cout<<"Destruyendo jugador\n";
}

int Jugador::pagar(int n){
	if(n <= dinero){
		dinero -= n;
		pot += n;
		return n;
	}
	else
		return -1;
}

int Jugador::cobrar(int n){
	dinero +=n;
	return dinero;
}

int Jugador::recibirMano(Carta* u, Carta* d){
	mano.first = u;
	mano.second = d;
	return 1;
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

int Jugador::getPot(){
	return pot;
}

void Jugador::emptyPot(){
	pot = 0;
}

bool Jugador::getActivo(){
	return activo;
}

void Jugador::desactivar(){
	activo = false;
}

void Jugador::activar(){
	activo = true;
}

std::pair<Carta*, Carta*> Jugador::getMano(){
	return mano;
}
