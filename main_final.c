#include "server_protocol.h"
#include "client_protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]){

	if (argc < 2) {
		return 1;
	}

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
		printf("Server\n\n");
		server_protocol_t sv_protocol;
		if (server_protocol_init(&sv_protocol, "7777", m) == 1) {
			return 1;
		}
		while (1) {
			if (server_protocol_process(&sv_protocol) == 1) {
				server_protocol_release(&sv_protocol);
				return 0;
			}
		}

	}

	else if (strcmp(argv[1], "client") == 0) {
		printf("Client\n\n");
		client_protocol_t client;
		client_protocol_init(&client, "localhost", "7777");
		while (1) {
			client_protocol_process_input(&client);
		}		
		
	}

	return 0;

}