#include "server.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	char buf_receiver[5] = "Chau"; //Esto se va rellenando con lo que manda el user
	char *buf_transmissor = "Hola\n";
	client_t client;
	if (strcmp(argv[1], "server") == 0) {
		server_t server;
		printf("server mode\n");
		server_init(&server, "7777");
		server_accept_client(&server);  //accept frena la ejecucion hasta conseguir cliente
		while (1) {
		printf("Cant de bytes recibidos: %d",server_recv_message(&server, buf_receiver, 5));
		//server_send_message(&server, buf_transmissor, 5); tambien se puede hacer q el servidor mande mensajes a la otra consola
		printf("%s\n", buf_receiver);
		}
	}


	else if (strcmp(argv[1], "client") == 0) {
		printf("client mode\n");
		if (client_init(&client, "localhost", "7777") != 0){
			return 1;
		}
		int cant;
		while (1) {
			cant = client_send_message(&client, buf_transmissor, 4);
			//cant = client_recv_message(&client, buf_receiver, 5);
			if (cant != -1){
				printf("Cant de bytes recibidos: %d\n", cant);
			}		
		}
	}

	return 0;
}

/*podria tener un tda protocolo cliente y otro protocolo servidor, inicializarlos en el main y que x ejemplo 
el tda protocolo server tiene una funcion procesar y en el main pongo un loop infinito y voy procesando los requests
que me hace el cliente. el tda protocolo conoceria a sudoku y usaria un tda cliente y un tda servidor para ir mandando
y coordinando los mensajes*/

//Netcat nos toma el barra n del enter por lo cual nos da el salto del inea