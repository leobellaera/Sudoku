#include "server_socket.h"
#define BACKLOG 1

int server_socket_init(server_socket_t* self, const char* port) {
	socket_init(&self->sv_skt);
	socket_init(&self->peer_skt);
	return socket_bind_and_listen(&self->sv_skt, port, BACKLOG);
}

int server_socket_accept_client(server_socket_t* self) {
	return socket_accept_client(&self->sv_skt, &self->peer_skt);
}

int server_socket_recv_message(server_socket_t* self, char* buf, int size) {
	return (socket_recv_message(&self->peer_skt, buf, size) == -1);
}

int server_socket_send_message(server_socket_t* self, char* buf, int size) {
	return (socket_send_message(&self->peer_skt, buf, size) == -1);
}

void server_socket_release(server_socket_t* self) {
	socket_release(&self->sv_skt);
	socket_release(&self->peer_skt);
}
