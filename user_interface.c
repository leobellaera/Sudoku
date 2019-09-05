#include "user_interface.h"
#include "client_protocol.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_COMMAND "exit"

#define FGETS_SIZE 14

#define SUCCESS 0
#define ERROR 1
#define EXIT 2
#define INVALID_COMMAND 3

int process_user_input(char* input);
int execute_command(client_protocol_t* protocol, char* command);
bool command_has_invalid_indexes(char* input);
bool command_has_invalid_values(char* input);
char* get_command(char* input);

int user_interface_init(user_interface_t* user_interface, const char* host, const char* service) {
	if (client_init(&user_interface->client, host, service)) {
		return ERROR;
	}
	client_protocol_init(&user_interface->protocol, &user_interface->client);
	return SUCCESS;
}

//Coordinates execute_command and get_user_input to read user input, 
//executes the command and releases resources if necessary.
//Returns 1 if ERROR or 0 if SUCCESS

int user_interface_process(user_interface_t* user_interface) { //
	char buffer[FGETS_SIZE];
	int input_state = process_user_input(buffer);
	if (input_state == EOF) {
		client_release(&user_interface->client);
		return ERROR;
	}
	if (input_state == INVALID_COMMAND) {
		return SUCCESS;
	}
	if (strcmp(buffer, EXIT_COMMAND) == 0) {
		client_release(&user_interface->client);
		return EXIT;
	}
	if (execute_command(&user_interface->protocol, buffer)) {
		client_release(&user_interface->client);
		return ERROR;
	}
	return SUCCESS;
}

//Executes the command printing on stdout the server answer.

int execute_command(client_protocol_t* protocol, char* command) {
	int command_exec = client_protocol_send_message(protocol, command);
	if (command_exec == ERROR) {
		return ERROR;
	}
	char* sv_ans = client_protocol_recv_answer(protocol);
	if (!sv_ans) {
		return ERROR;
	}
	printf("%s\n", sv_ans);
	free(sv_ans);
	return SUCCESS;
}

//Asks user for input. Returns 1 if eof or invalid input, 0 in other case

int process_user_input(char* input) {
	printf("Ingresá un comando: ");
	if (!fgets(input, FGETS_SIZE, stdin)) {
		return EOF;
	}
	input[strlen(input) - 1] = '\0'; //replace '\n' with '\0'
	if (command_has_invalid_indexes(input)) {
		printf("​Error en los índices. Rango soportado: [1,9]\n​");
		return INVALID_COMMAND;
	}
	else if (command_has_invalid_values(input)) {
		printf("​Error en el valor ingresado. Rango soportado: [1,9]\n​");
		return INVALID_COMMAND;
	}
	return SUCCESS;
}

bool command_has_invalid_indexes(char* input) {
	return false;
}

bool command_has_invalid_values(char* input) {
	return false;
}

char* get_command(char* input) {
	int i = 0;
	while (input[i] != '\0' && input[i] != ' ') {
		i++;
	}
	char* command = malloc(sizeof(char)* i + 1);
	command[i] = '\0';
	for (int j = 0; j < i; j++) {
		command[j] = input[j];
	}
	return command;
}