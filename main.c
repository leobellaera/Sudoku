#include "server_protocol.h"
#include "user_interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXIT 2
#define ERROR 1
#define SUCCESS 0

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
		user_interface_t user_interface;
		user_interface_init(&user_interface, "localhost", "7777");
		int state;
		while (1) {
			state = user_interface_process(&user_interface);
			if (state == ERROR) {
				return 1;
			}
			else if (state == EXIT) {
				return 0;
			}
		}		
		
	}

	return 0;

}