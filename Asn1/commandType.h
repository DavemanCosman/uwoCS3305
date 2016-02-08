#ifndef commandType_h
#define commandType_h

#include "constants.h"
#include "bool.h"

/* commandType structure
 * Holds relevant command information
 * - line: the input given by user
 * - args: the parsed tokens to be executed as commands
 * - IOin: points to the parsed token after IO redirect in
 * - IOout: points to the parsed token after IO redirect out
 * - firstCommand: true if it's first command in line, false otherwise
 * - lastCommand: true if it's last command in line, false otherwise
 * ^ last two bools used for handling piping
 */
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
