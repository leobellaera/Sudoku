#include "server_protocol.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]){

	int m[9][9] = {
        {0,0,1,0,0,0,0,3,5},
        {0,0,0,0,0,0,0,0,0},
        {6,0,0,0,0,0,0,0,0},
        {1,0,0,0,4,0,0,0,0},
        {2,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,0,0,0},
        {0,0,0,0,0,4,0,0,0}
	};

	if (strcmp(argv[1], "server") == 0) {
		printf("Server mode\n");
		server_protocol_t sv_protocol;
		server_protocol_init(&sv_protocol, "7777", m);
		server_protocol_process(&sv_protocol);
	}

	else if (strcmp(argv[1], "client") == 0) {
		printf("Client mode\n");
		client_t cliente;
		client_init(&cliente, "localhost", "7777");
		char mess = 'G';
		client_send_message(&cliente, &mess, 1);
		char aux[4];
		char buff[723];
		client_recv_message(&cliente, aux, 4);
		client_recv_message(&cliente, buff, 723);
		printf("%s", buff);
	}

	return 0;

}