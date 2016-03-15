ALL: servidor cliente
.PHONY=clean prueba

clean:
	\rm -f servidor cliente prueba

servidor: servidor.cpp
	g++ servidor.cpp -o servidor

cliente: cliente.cpp
	g++ cliente.cpp -o cliente

prueba: main.cpp Baraja.cpp Carta.cpp
	g++ --std=c++11 main.cpp Baraja.cpp Carta.cpp -o prueba
