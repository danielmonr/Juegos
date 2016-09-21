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

#pragma once

#include "Carta.h"
#include <pthread.h>
#include <iostream>
#include <unistd.h>

class Jugador{
	private:
		int numero;
		int dinero;
		bool activo;
		int pot;
		int fd;
		std::pair<Carta*, Carta*> mano;
		pthread_t pth;

	public:
		Jugador();
		Jugador(int, int);
		~Jugador();
		int pagar(int);
		int cobrar(int);
		int recibirMano(Carta*, Carta*);	
		int getFileDescriptor();
		int getNum();
		int getDinero();
		int getPot();
		bool getActivo();
		void desactivar();
		void activar();
		void emptyPot();
		std::pair<Carta*, Carta*> getMano();
		static void* recibirmsg(void*);
};

#endif
