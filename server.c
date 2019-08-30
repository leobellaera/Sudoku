#include "server.h"
#define BACKLOG 1

int server_init(server_t* sv, const char* port) {
	socket_init(&sv->sv_skt);
	socket_init(&sv->peer_skt);
	return socket_bind_and_listen(&sv->sv_skt, port, BACKLOG);
	//sudoku_init();
	//char buffer = NULL;
}

/* int server_connect(server_t* sv, const char* port) {          //Quizas podria sacar un par de cosas del init y poner esto
	return socket_bind_and_listen(sv->skt, port, BACKLOG);
}*/

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