#ifndef commandExecute_h
#define commandExecute_h

#include "commandType.h"

// Executes and handles the chaining of commands via pre-existing pipe forking and IO redirection. 
void commandExecute (struct commandType* command, int* pipes, int input_fd);

#endif
