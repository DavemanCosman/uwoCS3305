#ifndef commandType_h
#define commandType_h

#include "constants.h"
#include "bool.h"

// Simple structure to hold the command information
struct commandType
{
	char* line;
	char* args[CMD_MAX];
	char* IOin;
	char* IOout;
	bool firstCommand;
	bool lastCommand;
};

// Method to execute a command, which will handle forking and piping
int run (struct commandType* command, int input);

#endif
