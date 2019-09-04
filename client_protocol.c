#include "client_protocol.h"
#include "protocol_message_parser.h"
#include <stdio.h>
#include <arpa/inet.h>
#define FGETS_SIZE 14
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*
ESTE TDA RECIBIRA UN INPUT YA LIMPIO (SIN LOS BARRA N AL FINAL) Y HARA TODAS LAS OPERETAS.. NUNCA HARA PRINTS! LE PASA A LA INTERFAZ EL TEXTO Y
LA INTERFAZ DECIDE QUE HACER.. EXIT YA NO SERA UN COMANDO (TENDREMOS UN METODO QUE SEA CLIENT_PROTOCOL_RELEASE ENTONCES SI LA INTERFAZ DETECTA 
UN EXIT, LIBERA LOS RECURSOS Y TERMIAN SU EJECUCION)
*/

bool input_is_valid(char* command);			//ESTO IRA EN LA INTERFAZ DEL USUARIO (TDA: SUDOKU_USER_INTERFACE)
int process_exit_command(client_protocol_t* protocol);
char* recv_command_answer(client_protocol_t* protocol);
int send_command_message(client_protocol_t* protocol, char* message, size_t mes_len);
int process_command(client_protocol_t* protocol, char* input);

int client_protocol_init(client_protocol_t* protocol, const char* host, const char* service) {
	if (client_init(&protocol->client, host, service)) {
		return 1;
	}
	return 0;
}

int client_protocol_process_input(client_protocol_t* protocol) {
	char input[FGETS_SIZE];
	printf("Enter a new command: ");
	if (!fgets(input, FGETS_SIZE, stdin)) { //if eof, resources are released
		client_release(&protocol->client);
		return 1;
	}
	if (!input_is_valid(input)) {
		printf("The command entered is invalid.\n");
		return 0;
	}

	if (process_command(protocol, input) == 1) {  //if process_command returns 1, resources are released
		client_release(&protocol->client);
		return 1;
	}
	return 0;
}

int process_command(client_protocol_t* protocol, char* input) {
	if (strcmp("exit\n", input) == 0) {
		return process_exit_command(protocol);
	}
	char* message = parse_command_to_message(input);
	if (send_command_message(protocol, message, strlen(message))) {
		return 1;
	}
	free(message);
	char* sv_answer = recv_command_answer(protocol);
	printf("%s\n", sv_answer);
	free(sv_answer);
	return 0;
}

int process_exit_command(client_protocol_t* protocol) {
	client_release(&protocol->client);
	return 1;
}

bool input_is_valid(char* command) {
	return true;  //**********************************************************************************************
}

char* recv_command_answer(client_protocol_t* protocol) {
	char len_buffer[5];
	len_buffer[4] = '\0';
	if (client_recv_message(&protocol->client, len_buffer, 4)) {
		return NULL;
	}
	uint32_t text_len = *(uint32_t *)len_buffer;
	text_len = ntohl(text_len);
	char* text_buffer = malloc(sizeof(char)*text_len + 1);
	text_buffer[text_len] = '\0';

	if (client_recv_message(&protocol->client, text_buffer, text_len)) {
		free(text_buffer);
		return NULL;
	}
	return text_buffer;
}

int send_command_message(client_protocol_t* protocol, char* message, size_t mes_len) {
	if (client_send_message(&protocol->client, message, mes_len)) {
		client_release(&protocol->client);
		return 1;
	}
	return 0;
}