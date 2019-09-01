#include "server.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char buf_receiver[5] = "Chau"; //Esto se rellenara con Hola
	char buf_transmitter[5] = "Hola";
	client_t client;
	if (strcmp(argv[1], "server") == 0) {
		server_t server;
		printf("server mode\n");
		server_init(&server, "7777");
		server_accept_client(&server);  //accept frena la ejecucion hasta conseguir cliente
		server_recv_message(&server, buf_receiver, 5);
		printf("%s\n", buf_receiver);
	}

	else if (strcmp(argv[1], "client") == 0){
		printf("client mode\n");
		client_init(&client, "localhost", "7777");
		printf("\nCantidad de bytes enviados: %d\n",client_send_message(&client, buf_transmitter, 5));
	}

	return 0;
}