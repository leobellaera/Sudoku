#include "client_socket.h"

int client_socket_init(client_socket_t* self, const char* host, 
	const char* service) {
	socket_init(&self->skt);
	return socket_connect(&self->skt, host, service);
}

int client_socket_recv_message(client_socket_t* self, char* buf, int size) {
	return (socket_recv_message(&self->skt, buf, size) == -1);
}

int client_socket_send_message(client_socket_t* self, char* buf, int size) {
	return (socket_send_message(&self->skt, buf, size) == -1);
}

void client_socket_release(client_socket_t* self) {
	socket_release(&self->skt);
}
