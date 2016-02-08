#include "commandType.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commandParse.h"
#include "commandHistory.h"
#include "commandExecute.h"
#include "constants.h"

static int fork_count = 0; // keep count of forks using a local variable to commandType.c
// Method to tell the system to wait on current processes
static void forkWait()
{
	int i;
	for (i = 0 ; i < fork_count ; ++i) { 
		wait (NULL);
	}
}

static int runCommand (struct commandType* command, int input_fd)
{
	// Pipe methods;
	int pipes[2];
	pipe(pipes);
	// increase the fork counter, fork assign pid
	++fork_count;
	pid_t pid = fork();
	
	// if child process
	if (pid == 0) { 
		executeCommand (command, pipes, input_fd);
	}
 
	// Close open writeable input streams
	close(pipes[WRITE]);
	if (input_fd != 0) {
		close(input_fd);
	}
 
	// If it's the last command
	if((*command).lastCommand == true ) {
		close(pipes[READ]);
		forkWait();
	}
 
	return pipes[READ];
}

static inline void exitCommand( struct commandType* command )
{
	// Code for exit
	int userExit = 0;
	
	// Grab the userExit command, if provided
	if((*command).args[1] != NULL ) {
		userExit = -1;
	}

	exit(userExit);	
}

static inline void historyCommand( struct commandType* command )
{
	if((*command).args[1] != NULL ) {
		syslog (LOG_INFO, "Error: this history does not support arguments\n");
	}
	else {
		print_commandHistory();
	}
}

static bool internalCommandHandler( struct commandType* command )
{
	// exit command
	if (strcmp((*command).args[0], "exit" ) == 0) {
		exitCommand(command);
		return true;
	}

	// history command
	if (strcmp((*command).args[0], "history" ) == 0) {
		historyCommand(command);
		return true;
	}

	// not an internal command
	return false;
}

/* Main function to run the command given by input line.
 * - command: points to the given command structure
 * - input: 
 */
int run( struct commandType* command, int input )
{
	// Parse the given command
	commandParse (command);
	// Check that there is a command, ie not null
	if ((*command).line != NULL) {
		// Check for exit and history commands first
		if(!internalCommandHandler(command)) {
			return runCommand(command, input);			
		}
	}
	return 0;
}
