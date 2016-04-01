ALL: servidor
.PHONY=clean prueba


clean:
	\rm -f servidor cliente prueba

servidor: server.cpp Baraja.cpp Jugador.cpp Carta.cpp
	g++ --std=c++11 -pthread -g server.cpp Jugador.cpp Baraja.cpp Carta.cpp -o servidor

cliente: cliente.cpp
	g++ cliente.cpp -o cliente

prueba: main.cpp Baraja.cpp Carta.cpp Pantalla.cpp Jugador.cpp
	g++ --std=c++11 -I. main.cpp Baraja.cpp Carta.cpp Jugador.cpp Pantalla.cpp -o prueba -lncurses
