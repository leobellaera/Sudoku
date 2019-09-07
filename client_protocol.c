#include "client_protocol.h"
#include "protocol_message_maker.h"
#include <stdio.h>
#include <arpa/inet.h>
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

void client_protocol_init(client_protocol_t* protocol, client_socket_t* skt) {
	protocol->skt = skt;
}

char* client_protocol_recv_answer(client_protocol_t* protocol) {
	char len_buffer[4];
	if (client_socket_recv_message(protocol->skt, len_buffer, 4)) {
		return NULL;
	}
	uint32_t text_len;
	memcpy(&text_len, len_buffer, 4);
	text_len = ntohl(text_len);
	char* text_buffer = malloc(sizeof(char)*text_len + 1);
	text_buffer[text_len] = '\0';

	if (client_socket_recv_message(protocol->skt, text_buffer, text_len)) {
		free(text_buffer);
		return NULL;
	}
	return text_buffer;
}

int client_protocol_send_message(client_protocol_t* protocol, char* command) {
	char* message = build_protocol_message(command);
	if (client_socket_send_message(protocol->skt, message, strlen(message))) {
		free(message);
		return 1;
	}
	free(message);
	return 0;
}
