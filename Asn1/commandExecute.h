#ifndef commandExecute_h
#define commandExecute_h

#include "commandType.h"

// Executes the given command in the current context. 
// Handles the chaining of commands via pre-existing pipes and IO redirection. 
void execute_command( struct commandType* command, int* pipes, int input_fd );

#endif
