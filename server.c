#include "server.h"
#define BACKLOG 1

int server_init(server_t* sv, const char* port) {
	socket_init(&sv->sv_skt);
	socket_init(&sv->peer_skt);
	return socket_bind_and_listen(&sv->sv_skt, port, BACKLOG);
	//sudoku_t sudoku;
	//sudoku_init(&sudoku);
}

int server_accept_client(server_t* sv) {
	return socket_accept_client(&sv->sv_skt, &sv->peer_skt);
}

int server_recv_message(server_t* sv, char* buf, int size) {
	return socket_recv_message(&sv->peer_skt, buf, size);
}

int server_send_message(server_t* sv, char* buf, int size){
	return socket_send_message(&sv->peer_skt, buf, size);
}

void server_release(server_t* sv){
	socket_release(&sv->sv_skt);
	socket_release(&sv->peer_skt);
}


/*
void server_process_message(server_t* sv){
	char buffer[4];
	socket_recv_message(&sv->peer_skt, buffer, 1);
	if (sv->buffer == 'P') {
		server_recv_message(sv, &buffer[1], 3); ahora esperamos 3 bytes mas   **podria estar todo en una funcion que se llame process_P
		sudoku_put(buffer[1], buffer[2], buffer[3])
	} else if (sv->buffer == 'G') {
		process_G();

	} else if (sv->buffer == 'R') {
		process_R();
	}
}


en el main iria algo como: while (True):
								server_process_message(sv)


*********************************************************

EN EL MAIN: del lado del cliente tendremos algo asi como :
while (!feof(stdin)){  //(o while true)
	char str[80];

	printf("Enter a new command: ");
	fgets(str, 10, stdin);

	client_process_command(client, str);
}

**********************************************************


	****client_proccess_command(client_t* client, char* command){ //procesa el comando ingresado por el usuario y ve que mensaje mandar
			//if (command == get) //igual hay q sacar el salto de linea primero
				client_send_message(client, 'G');
		}


http://www.java2s.com/Code/C/Console/Usefgetstoreadstringfromstandardinput.htm



*/