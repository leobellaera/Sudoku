#include "client_interface.h"
#include "client_protocol.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_COMMAND "exit"
#define PUT_COMMAND "put"

#define FGETS_SIZE 25

#define SUCCESS 0
#define ERROR 1
#define EXIT 2
#define INVALID_COMMAND 3

#define INDEX_ERROR_MES "​Error en los índices. Rango soportado: [1,9]\n​"
#define VALUE_ERROR_MES "​Error en el valor ingresado. Rango soportado: [1,9]\n​"

int process_user_input(char* input);
int execute_command(client_protocol_t* protocol, char* command);
bool command_has_valid_indexes(char* input);
bool command_has_valid_values(char* input);
char* get_command_first_arg(char* input);
bool index_is_allowed(char* index);
bool value_is_allowed(char* value);

int client_interface_init(client_interface_t* client_interface, const char* host, const char* service) {
	if (client_init(&client_interface->client, host, service)) {
		return ERROR;
	}
	client_protocol_init(&client_interface->protocol, &client_interface->client);
	return SUCCESS;
}

//Coordinates execute_command and get_user_input to read user input, 
//executes the command and releases resources if necessary.
//Returns 1 if ERROR or 0 if SUCCESS

int client_interface_process(client_interface_t* client_interface) { //
	char buffer[FGETS_SIZE];
	int input_state = process_user_input(buffer);
	if (input_state == EOF) {
		client_release(&client_interface->client);
		return ERROR;
	}
	if (input_state == INVALID_COMMAND) {
		return SUCCESS;
	}
	if (strcmp(buffer, EXIT_COMMAND) == 0) {
		client_release(&client_interface->client);
		return EXIT;
	}
	if (execute_command(&client_interface->protocol, buffer)) {
		client_release(&client_interface->client);
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

//Asks user for input and checks user input. Returns 1 if eof or invalid input, 0 in other case

int process_user_input(char* input) {
	if (!fgets(input, FGETS_SIZE, stdin)) {
		return EOF;
	}
	input[strlen(input) - 1] = '\0'; //replace '\n' with '\0'
	if (!command_has_valid_indexes(input)) {
		fprintf(stdout, INDEX_ERROR_MES);
		return INVALID_COMMAND;
	}
	else if (!command_has_valid_values(input)) {
		fprintf(stdout, VALUE_ERROR_MES);
		return INVALID_COMMAND;
	}
	return SUCCESS;
}

//Checks if command indexes are allowed. 

bool command_has_valid_indexes(char* input) {
	char* command_first_arg = get_command_first_arg(input);
	if (strcmp(command_first_arg, PUT_COMMAND) == 0) {
		char index_a[4], index_b[4];
		index_a[3] = '\0';
		index_b[3] = '\0';
		sscanf(input, "%*s %*s %*s %3[^,]%*[, ]%3s", index_a, index_b); //scan of put indexes
		if (!index_is_allowed(index_a) || !index_is_allowed(index_b)) {
			free(command_first_arg);
			return false;
		}
	}
	free(command_first_arg);
	return true;
}

//Checks if command values are allowed.

bool command_has_valid_values(char* input) {
	char* command_first_arg = get_command_first_arg(input);
	if (strcmp(command_first_arg, PUT_COMMAND) == 0) {
		char value[4];
		value[3] = '\0';
		sscanf(input, "%*s %3s", value); //scan of put value
		if (!value_is_allowed(value)) {
			free(command_first_arg);
			return false;
		}
	}
	free(command_first_arg);
	return true;
}

//Finds and returns command first argument.

char* get_command_first_arg(char* input) {
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

bool index_is_allowed(char* index) {
	printf("%s\n", index);
	int idx = atoi(index);
	if (idx > 9 || idx < 1) {
		return false;
	}
	return true;
}

bool value_is_allowed(char* value) {
	printf("%s\n", value);
	int v = atoi(value);
	if (v > 9 || v < 1) {
		return false;
	}
	return true;
}