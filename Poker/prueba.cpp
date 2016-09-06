
#include 	"Juego.h"
#include 	"Jugador.h"
#include 	"Carta.h"
#include 	"Baraja.h"
#include	<stdlib.h>
#include    <iostream>
#include    <unistd.h>
#include    <stdio.h>
#include    <vector>
#include    <signal.h>

std::vector<Juego*> juegos;
Juego* j;

void manejarSenales(int c){
	std::cout << "Terminando Proceso...\n";
	std::cout << "Cerrando los juegos abiertos...\n";
	/*while(!juegos.empty()){
		Juego* aux = juegos.back();
		juegos.pop_back();
		//delete(aux);
	}*/
	Juego * temp;
	std::cout<< "Se encontraron " << juegos.size() << " juegos.\n";
	for(auto item:juegos){
		std::cout << "Borrando juego " << item->getId() << " ...\n";
		delete item;
	}
		//delete juegos[0];
	juegos.clear();
	std::cout<< "Liberando memoria...\n";
	std::cout<<"Programa Terminado.";
	signal(SIGINT, SIG_DFL);
	raise(SIGINT);
}

int main(int argc, char *argv[]){
	signal(SIGINT, manejarSenales);
	
	j = new Juego(8002,1);
	juegos.push_back(j);
	j->crearSocket();

	return 0;
}