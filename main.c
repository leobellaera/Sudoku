#include "server_interface.h"
#include "user_interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXIT 2
#define ERROR 1
#define SUCCESS 0

int main(int argc, char* argv[]){

	if (strcmp(argv[1], "server") == 0) {
		server_interface_t sv_interface;
		if (server_interface_init(&sv_interface, "7777")) {
			return 1;
		}
		while (1) {
			if (server_interface_process(&sv_interface)) {
				return 1;
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