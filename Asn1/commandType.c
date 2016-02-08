#include "commandType.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commandParse.h"
#include "commandHistory.h"
#include "commandExecute.h"
#include "constants.h"

static int fork_count = 0;
 
static void forkWait()
{
	int i;
	for (i = 0 ; i < fork_count ; ++i) { 
		wait (NULL);
	}
}

static int runCommand (struct commandType* command, int input_fd)
{
	++fork_count;
	int pipes[2];
	pipe(pipes);	

	pid_t pid = fork();
	// if child process
	if (pid == 0) { 
		//execute command here
		execute_command (command, pipes, input_fd);
	}
 
	// Close all open writeable streams
	close(pipes[WRITE]);
	if (input_fd != 0) close(input_fd);
 
	// If it's the last command
	if((*command).isLastCommand == true ) 
	{
		close(pipes[READ]);
		forkWait();
	}
 
	return pipes[READ];
}

static inline void exitCommand( struct commandType* command )
{
	int userExit = 0;
	
	// Grab the userExit command, if provided
	if((*command).args[1] != NULL ) {
		printf("error: exit does not support any extra arguments");
	}

	exit(userExit);	
}

static inline void historyCommand( struct commandType* command )
{
	if((*command).args[1] != NULL ) {
		printf("error: history does not support any extra arguments");
	}
	else {
		print_commandhistory();
	}
}

static bool handle_internal_command( struct commandType* command )
{
	// exit
	if (strcmp((*command).args[0], "exit" ) == 0) {
		exitCommand(command);
		return true;
	}

	// history
	if (strcmp((*command).args[0], "history" ) == 0) {
		historyCommand(command);
		return true;
	}

	// not an internal command
	return false;
}

int run( struct commandType* command, int input )
{
	commandParse (command);
	if ((*command).line != NULL) {
		if(!handle_internal_command(command)) {
			return runCommand(command, input);			
		}
	}
	return 0;
}
