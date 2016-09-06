/*
 * =====================================================================================
 *
 *       Filename:  Juego.h
 *
 *    Description:  Juego de poker, programa del sevidor. Debe aceptar hasta 5 jugadores.
 *					Manejador de partidas.
 *
 *        Version:  1.0
 *        Created:  22/08/16 16:44:28
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

 #include "Juego.h"

 Juego::Juego(){

 }

 Juego::~Juego(){
 	std::cout<<"Destruyendo Juego\n";
 	std::cout<< "Cancelando thread, regreso: " << pthread_cancel(nuevas_conec)<<std::endl;
 	wait(nuevas_conec);
 	//pthread_cancel(nuevas_conec);
 	std::cout<<"Cerrando el socket\n";
 	close(servidor);

 	//free(jugadores);
 	if(!jugadores.empty())
 	for (auto item:jugadores){
 		std::cout<<"Borrando jugador\n";
 		delete(item);
 	}
 	
 	/*std::cout<<"Cerrando el socket\n";
 	close(servidor);*/
 	std::cout<<"Salio del destructor.\n";
 }

 Juego::Juego(int tcp_port, int i){
 	std::cout<<"Creando Juego\n";
 	ip = "127.0.0.7";
 	TCP_PORT = tcp_port;
 	id = i;
 }

int Juego::crearSocket(){
	std::cout<<"Creando socket\n";
	//crear el servidor
	servidor = socket(PF_INET, SOCK_STREAM, 0);
	// Ligar socket con una direccion y puerto
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton(ip, &direccion.sin_addr);
	bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));

	// escuchar clientes
	listen(servidor, N);
	std::cout<<"Escuchando...\n";

	// Inicializar la variable del tamano del socket
	tam = sizeof(direccion);
	//sleep(5);
	pthread_create(&nuevas_conec, NULL, &Juego::buscarJugadores, this);
	while(j_conectados == 0){
		sleep(1);
	}
	enviarMensajeTodos("primer mensaje");
	sleep(10);
	recivirMensajeJugador(0);
	//enviarMensajeTodos("segundo mensaje");
	//sleep(5);
	//recivirMensajeJugador(0);
	pthread_join(nuevas_conec, NULL);
	return 1;
}
void* Juego::buscarJugadores(void *arg){
	Juego* actual = (Juego*)arg;
	std::cout<<"Buscando jugadores\n";
	actual->j_conectados = 0;
	while(true){
		std::cout<<"Instancia del while\n";
		if(actual->j_conectados < N){
			actual->cliente = accept(actual->servidor, (struct sockaddr *) &(actual->cli_addr), &(actual->tam));
			actual->jugadores.push_back(new Jugador((actual->jugadores).size(), actual->cliente));
			(actual->j_conectados)++;
			std::cout << "Coneccion exitosa! num jugadores: " << actual->j_conectados << "\n";
		}
	}
}
int Juego::manejarConeccionesActivas(){
	return 1;
}
int Juego::iniciarPartida(){
	return 1;
}
int Juego::terminarPartida(){
	return 1;
}
int Juego::Repartir(){
	return 1;
}
int Juego::destapar(){
	return 1;
}
int Juego::desechar(){
	return 1;
}
int Juego::pagar(){
	return 1;
}
int Juego::asignarRoles(){
	return 1;
}
int Juego::rondaApuestas(){
	return 1;
}
int Juego::rondaUno(){
	return 1;
}
int Juego::enviarMensajeJugador(){
	return 1;
}
int Juego::enviarMensajeTodos(char * msg){
	std::cout << "Tamano mensaje: " << strlen(msg) << std::endl;
	for (auto jug:jugadores){
		// int escritos = write(jug->getFileDescriptor(), msg, strlen(msg));
		int escritos = send(jug->getFileDescriptor(), msg, strlen(msg), MSG_CONFIRM);
		if(escritos != strlen(msg)){
			std::cout << "Error en envio para jugador " << jug->getNum() <<", enviados: " << escritos << std::endl;
		}
		else{
			std::cout<< "Envio exitoso a jugador " << jug->getNum() << std::endl;
		}
	}
	return 1;
}
int Juego::recivirMensajeJugador(int num){
	char buff[25];
	int retorno = read(jugadores[num]->getFileDescriptor(), &buff, sizeof(buff));
	if (retorno < 1){
		std::cout << "Error en la coneccion, retorno: " << retorno << std::endl;
	}
	else{
		std::cout << "Coneccion exitosa, retorno: " << retorno << std::endl;
		std::string str(buff);
		std::cout << "mensaje: " << str << std::endl;
	}
	return 1;
}
int Juego::transformarAInt(){
	return 1;
}
int Juego::getId(){
	return id;
}
int Juego::quitarJugador(int jug){
	return 1;
}