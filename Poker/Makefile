ALL: servidor
.PHONY=clean prueba


clean:
	\rm -f servidor cliente prueba

servidor: server.cpp Baraja.cpp Jugador.cpp Carta.cpp
	g++ --std=c++11 -pthread -g server.cpp Jugador.cpp Baraja.cpp Carta.cpp -o servidor

cliente: cliente.cpp
	g++ cliente.cpp -o cliente

prueba: prueba.cpp Baraja.cpp Carta.cpp Pantalla.cpp Jugador.cpp Juego.cpp
	g++ --std=c++11 -I. prueba.cpp Baraja.cpp Carta.cpp Jugador.cpp Pantalla.cpp Juego.cpp -o prueba -lncurses -pthread
