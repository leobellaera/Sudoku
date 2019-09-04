#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol_message_parser.h"

#define PUT_MESSAGE_LEN 4
#define NO_ARGS_COMMAND_LEN 1 //command with no arguments
#define RESET_COMMAND_CODE 'R'
#define PUT_COMMAND_CODE 'P'
#define VERIFY_COMMAND_CODE 'V'
#define GET_COMMAND_CODE 'G'

bool command_has_arguments(char* command);
void build_protocol_message(char* command, char* message);
void build_g_message(char* message);
void build_r_message(char* message);
void build_v_message(char* message);
void build_p_message(char* message, char* command);

char* parse_command_to_message(char* command) {
	command[strlen(command) - 1] = '\0'; // '\n' is replaced by '\0'  (interface job!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
	char* message;
	if (!command_has_arguments(command)) {
		message = malloc(sizeof(char)*NO_ARGS_COMMAND_LEN + 1);
		message[NO_ARGS_COMMAND_LEN] = '\0';
	} else {
		message = malloc(sizeof(char)*PUT_MESSAGE_LEN + 1);
		message[PUT_MESSAGE_LEN] = '\0';
	}
	build_protocol_message(command, message);
	return message;
}

void build_protocol_message(char* command, char* message) {
	if (strcmp("get", command) == 0) {
		build_g_message(message);
	}
	else if (strcmp("reset", command) == 0) {
		build_r_message(message);
	}
	else if (strcmp("verify", command) == 0) {
		build_v_message(message);
	}
	else {
		build_p_message(message, command);
	}
}

void build_g_message(char* message) {
	message[0] = GET_COMMAND_CODE;
}

void build_r_message(char* message) {
	message[0] = RESET_COMMAND_CODE;
}

void build_v_message(char* message) {
	message[0] = VERIFY_COMMAND_CODE;
}

void build_p_message(char* message, char* command) { //command format: "put x in y,z"
	message[0] = PUT_COMMAND_CODE;
	message[1] = command[9];
	message[2] = command[11];
	message[3] = command[4];
}

bool command_has_arguments(char* command) {
	size_t len = strlen(command);
	for (int i=0; i < len; i++) {
		if (command[i] == ' ') {
			return true;
		}
	}
	return false;
}

