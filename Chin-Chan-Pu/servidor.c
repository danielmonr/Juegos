
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define TCP_PORT 8000

#define ROCA 'a'
#define PAPEL 's'
#define TIJERAS 'd'

int servidor, cliente;

int jugar(char, char);
void cerrar(int);

int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char respuesta;
	char adversario;
	int gano;
	int cont = 0;
	int cont2 = 0;
    
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);

	signal(SIGINT, cerrar);
    
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer de socket y escribir en pantalla
        while (leidos = read(fileno(stdin), &respuesta, sizeof(char))) {
            printf("Respuesta: %c\n", respuesta);
			write(cliente, &respuesta, sizeof(char));
            leidos = read(cliente, &adversario, sizeof(char));
			printf("Adversario: %c\n", adversario);
			gano = jugar(respuesta, adversario);
			if(gano == 1){
				printf("Ganaste! :D\n");
				cont++;
			}
			else if(gano == 0){
				cont--;
				printf("Perdiste :C\n");
			}
			else{
				printf("EMPATE :|\n");
			}
			write(cliente, &gano, sizeof(int));

        }     
    }
    
    // Cerrar el socket
    
    close(servidor);
    close(cliente);
    
    return 0;
}

void cerrar(int sig){
	close(servidor);
	close(cliente);
}

int jugar(char yo, char tu){
	if (yo == tu)
		return -1;
	if(yo == ROCA){
		if(tu == PAPEL)
			return 0;
		else if(tu == TIJERAS)
			return 1;
	}
	else if(yo == PAPEL){
		if(tu == ROCA)
			return 1;
		else if(tu == TIJERAS)
			return 0;
	}
	else if(yo == TIJERAS){
		if(tu == PAPEL)
			return 1;
		else if (tu == ROCA)
			return 0;
	}

	return 0;
}
