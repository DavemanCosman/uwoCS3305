#ifndef commandType_h
#define commandType_h

#include "constants.h"

// Simple structure to hold the command information
struct commandType
{
	char* command;
	char* args[CMD_MAX];
	char* IOin;
	char* IOout;
};

#endif
