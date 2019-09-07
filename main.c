#include "sudoku_interface.h"

#define SUCCESS 0
#define ERROR 1
#define EXIT 2

int main(int argc, char* argv[]){
	sudoku_interface_t sudoku_interface;

	int game_init = sudoku_interface_init(&sudoku_interface, argc, argv);
	if (game_init == ERROR) {
		return 1;
	}

	int execution;
	while(1) {
		execution = sudoku_interface_execute(&sudoku_interface);
		if (execution == EXIT) {
			return SUCCESS;
		} else if (execution == ERROR) {
			return ERROR;
		}
 	}
	return 0;
}
