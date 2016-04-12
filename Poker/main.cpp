/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 12:42:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <iostream>
#include    <unistd.h>
#include    <stdio.h>
#include    <vector>
#include    "Carta.h"
#include    "Baraja.h"
#include    "Pantalla.h"
#include    "Jugador.h"

#define SIZE_BUFFER 256

//char* escribir();
//
using namespace std;
void jugar();
void Ronda();

const int cli_count = 5;
/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Baraja *b = new Baraja();
	b->revolver();
	Jugador* j = new Jugador(1, 300);
	
	vector<Carta*> v;
	v.push_back(c);

	//cout << c->getRepre()<< endl;
	/*
	Pantalla::startCurses(2);
	//Pantalla::print("hola");
	Pantalla::printInfo(j);
	Pantalla::printGame(v, 200);
	
	Pantalla::escribirDialog();
	Pantalla::endCurses();*/


	/*initscr();
	printw("Main window");
	WINDOW* sb = newwin(10,20,5,15);
	refresh();
	box(sb, 0, 0);
	mvwprintw(sb,1,1, "subwindow");
	refresh();
	wrefresh(sb);
	getch();
	delwin(sb);
	endwin(); */
/*

	char buff[120];
	sprintf(buff, "/t%d", 32);
	printf("el buffer contiene: %s, de tamano: %d\n", buff, (int)strlen(buff));
	sprintf(buff, "l");
	printf("ahora contiene: %s, de tamano: %d\n", buff, (int)strlen(buff));
*/


	//jugar();

	//free(b);
	//free(j);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*
char* escribir(){
	bool activo = true;
	int cont = 0;
	while (activo && cont < SIZE_BUFFER){
		int ch = wgetch(Pantalla::dispDialog);
		switch(ch){
			case 27:
				activo = false;
				break;
			case '\n':
				return buffer;
				break;
			default:
				waddch(Pantalla::dispDialog, ch);
				break;
		}
	}
}*/

int grande, chica, repartir, turno,  apuesta, pot, j_max, nuevo;
int num_ronda = 0;
int num_cartas = 0;
int pots[cli_count];
void jugar(){
	cout << "Nueva mano" << endl;
	repartir = 1;
	cout << "Crear baraja, revolver baraja.\n";
	cout << "Asignar cartas a jugadroes.\n";
	cout << "Enviar mensaje de asignacion de numero a jugadores.\n";
	for (int i = 0; i < cli_count; ++i){
		cout << "Enviar mensaje de asignacion a cada jugador /j" << i+1 << "/carta1/carta2" << endl;
	}

	for(int i = 0; i < cli_count; ++i){
		pots[i] = 0;
	}
	Ronda();
}


void Ronda(){
	char buff[120];
	apuesta = 15;
	pot = 0;
	string mnsj;
	bool jugando = true;
	bool ronda_apuestas;
	cout << "Mensaje de empezar" << endl;
	grande = repartir -2;
	chica = repartir -1 ;
	if (grande < 1){
		grande = cli_count + grande;
	}
	j_max = grande;

	if (chica < 1){
		chica = cli_count +chica;
	}
	turno = grande -1;
	if(turno < 1){
		turno = cli_count + turno;
	}

	cout << "Mensaje de dealer /d" << repartir << endl;

	cout << "Mensaje de grande /g" << grande << "/" << apuesta << endl;
	cout << "Esperar a que page, recibir mensaje de jugador " << grande << endl;
	pot += apuesta;
	pots[grande-1] = apuesta;
	cout << "Actualizar el pot " << pot << endl;
	cout << "Enviar mensaje de actualizacion de pot" << endl;
	cout << "Esperar mensaje de chica, jugador  /c" << chica << "/" << apuesta/2 << endl;
	pot += apuesta/2;
	pots[chica-1] = apuesta/2;
	cout << "Actualizar el pot " << pot << endl;
	cout << "Enviar mensaje de actualizacion de pot" << endl;
	ronda_apuestas = true;
	for (int rt = 0; rt < 3; rt++){
		cout << "Enviar mensaje de cominezo de ronda /r" << num_ronda << endl;
		if (num_ronda == 1){
			cout << "destapar 3 cartas" << endl;
			num_cartas = 3;
		}
		else if(num_ronda == 2 || num_ronda == 3){
			cout << "Destapar una carta" << endl;
			num_cartas ++;
		}
		cout << "Enviar informacion ronda /a/num_ronda/pot/num_cartas/carta1/carta2/../cartan" << endl;
		
		while(ronda_apuestas){
			cout << "Enviar mensaje de turno de jugador " << turno << endl;
			cout << "Esperar mensaje de opcion de jugador " << turno << endl;
			nuevo = 0;
			while(nuevo == 0){
				cin >> mnsj;
				if (mnsj[1] == 'm' || mnsj[1] == 'i'){
					for(int i = 2; i < mnsj.length(); ++i){
						nuevo *= 10;
						nuevo += (mnsj[i] - '0');
					}
					cout << "Evaluar que la apuesta se igual o mayor que la maxima" << endl;
					if((nuevo+ pots[turno-1]) < apuesta){
						nuevo = 0;
						cout << "Se envia mensaje de error al jugador.\n" << endl;
						cout << "Error en el calculo, se repite el input.\n" << endl;
					}
				}
			}
			pot += nuevo;
			pots[turno-1] += nuevo;
			cout << "actualizar pot con " << nuevo << " total: " << pot << endl;
			cout << "Enviar opcion de jugador a todos " << mnsj << endl;
			cout << "Enviar mensaje de actualizacion de pot" << endl;
			if(mnsj[1] == 'm'){
				j_max = turno;
				apuesta = pots[turno-1];
			}
			turno--;
			if (turno == 0){
				turno = cli_count;
			}
			cout << "turno : " << turno << " j_max: " << j_max << endl;
			if(turno == j_max){
				ronda_apuestas = false;
				num_ronda++;
			}
		}
	}

}
