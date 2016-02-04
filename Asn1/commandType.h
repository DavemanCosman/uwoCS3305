#ifndef commandType_h
#define commandType_h

#include "bool.h"
#include "constants.h"

// Simple structure to hold the command information
struct commandType
{
	char* command;
	char* args[CMD_MAX];
	char* IOin;
	char* IOout;
	bool isFirstToken;
	bool isLastToken;
};

/* Uses execvp to run a command
 * Method concerned with forking and piping
 */
int run(struct commandType* command, int input);

#endif
