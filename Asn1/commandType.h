#ifndef commandType_h
#define commandType_h

#include "bool.h"

// Simple structure to hold the command information
struct commandType
{
	char* token;
	char* args[10];
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
