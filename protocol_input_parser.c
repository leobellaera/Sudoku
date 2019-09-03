#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool input_has_several_arguments(char* input);
void make_protocol_message(char* input, char* message);

char* parse_input_to_message(char* input) {
	input[strlen(input) - 1] = '\0'; // '\n' is replaced by '\0'
	char* message;
	if (!input_has_several_arguments(input)) {
		message = malloc(sizeof(char) + 1);
		message[1] = '\0';
	} else {
		message = malloc(sizeof(char)*4 + 1);
		message[4] = '\0';
	}
	make_protocol_message(input, message);
	return message;
}

void make_protocol_message(char* input, char* message) {
	if (strcmp("get", input) == 0) {
		message[0] = 'G';
	}
	else if (strcmp("reset", input) == 0) {
		message[0] = 'R';
	}
	else if (strcmp("verify", input) == 0) {
		message[0] = 'G';
	}
	else {
		message[0] = 'P';
		message[1] = input[9] - 1;
		message[2] = input[11] - 1;
		message[3] = input[4];
	}
}

bool input_has_several_arguments(char* input) {
	size_t len = strlen(input);
	for (int i=0; i < len; i++) {
		if (input[i] == ' ') {
			return true;
		}
	}
	return false;
}

