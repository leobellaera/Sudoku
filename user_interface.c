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

int get_user_input(char* input);
int execute_command(client_protocol_t* protocol, char* command);
void print_if_invalid_command(char* input);
void print_if_invalid_args(char* input);
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

int user_interface_process(user_interface_t* user_interface) {
	char input[FGETS_SIZE];
	if (get_user_input(input) == ERROR) {
		client_release(&user_interface->client);
		return ERROR;
	}
	if (strcmp(input, EXIT_COMMAND) == 0) {
		client_release(&user_interface->client);
		return EXIT;
	}
	if (execute_command(&user_interface->protocol, input)) {
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

int get_user_input(char* input) {
	printf("Ingresá un comando: ");
	if (!fgets(input, FGETS_SIZE, stdin)) {
		return ERROR;
	}
	input[strlen(input) - 1] = '\0'; //replace '\n' with '\0'
	print_if_invalid_command(input);
	print_if_invalid_args(input);
	return SUCCESS;
}

void print_if_invalid_command(char* input) {
	const char* invalid_command_message = "El comando ingresado es inválido\n";
	const char *valid_commands[5] = {"put", "verify", "reset", "get", "exit"};
	char* command = get_command(input);
	for (int i = 0; i < 5; i++) {
		if (strcmp(command, valid_commands[i]) == 0) {
			free(command);
			return;
		}
	}
	printf("%s", invalid_command_message);
}

void print_if_invalid_args(char* input) {
	
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