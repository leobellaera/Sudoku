#include "client.h"

int client_init(client_t* client, const char* host, const char* service) {
	socket_init(&client->skt);
	return socket_connect(&client->skt, host, service);
}

int client_recv_message(client_t* client, char* buf, int size) {
	return (socket_recv_message(&client->skt, buf, size) == -1);
}

int client_send_message(client_t* client, char* buf, int size) {
	return (socket_send_message(&client->skt, buf, size) == -1);
}

void client_release(client_t* client) {  //destroy
	socket_release(&client->skt);
}