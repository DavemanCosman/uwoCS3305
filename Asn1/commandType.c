#include "commandType.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commandParse.h"
#include "commandHistory.h"
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

/* runCommand
 * Pipes command and passes it to execute method
 * handles write and read streams
 * returns the file descriptor from the piped command
 * - command: the command to be handled
 * - input_fd: the input file descriptor (for piping)
 */
static int runCommand (struct commandType* command, int input_fd)
{
	int pipes[2];
	pipe(pipes);
	// increase the fork counter, fork and assign pid
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
 
	// If it's the last command, close the read stream
	if((*command).lastCommand == true ) {
		close(pipes[READ]);
		forkWait();
	}
 
	return pipes[READ];
}

/* exitCommand
 * internal built in exit command
 * runs if the exit command was given.
 * will not be successful if there are more given arguments
 */
static inline void exitCommand(struct commandType* command)
{
	// Code for exit
	int userExit = 0;
	
	// Grab the userExit command, if provided
	if((*command).args[1] != NULL ) {
		userExit = -1;
	}
	// run exit command
	exit(userExit);	
}

/* historyCommand
 * internal built in history command
 * runs if the history command was given.
 * will not be successful if there are more given arguments
 */
static inline void historyCommand(struct commandType* command)
{
	// According to assignment, history should only print last 10 commands
	if((*command).args[1] != NULL ) {
		syslog (LOG_INFO, "Error: this history does not support arguments\n");
	}
	// Print the command history if proper input is given
	else {
		print_commandHistory();
	}
}

/* internalCommandHandler
 * handles internal commands when given and passes it accordingly.
 * will return false if not an internal command
 */
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

/* Run the command given by input line and handle it
 * - command: points to the given command structure
 * - input: returns value from previous command, used for piping
 */
int run(struct commandType* command, int input)
{
	// Parse the given command using the parser
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

/* executeCommand
 * Handles forking, piping and IO redirection here
 * - command: pointer to given command structure to interpret
 * - pipes: pointer to the amount of pipes
 * - input_fd: input file descriptor, used for piping
 * SCHEME:
 *	STDIN --> O --> O --> O --> STDOUT
 */
void executeCommand( struct commandType* command, int* pipes, int input_fd )
{
	FILE* file_in = NULL;
	FILE* file_out = NULL;

	// First command
	if( (*command).firstCommand == true && (*command).lastCommand == false && input_fd == 0) {
		dup2(pipes[WRITE], STDOUT_FILENO);
	} 
	// Middle commands
	else if((*command).firstCommand == false && (*command).lastCommand == false && input_fd != 0 ) {
		dup2(input_fd, STDIN_FILENO);
		dup2(pipes[WRITE], STDOUT_FILENO);
	} 
	// Last command
	else {
		dup2(input_fd, STDIN_FILENO);
	}

	// stdin is redirected
	if( (*command).IOin ) {
		file_in = fopen((*command).IOin, "r");
		dup2(fileno(file_in), STDIN_FILENO );
	}
	
	// stdout is redirected
	if((*command).IOout) {
		file_out = fopen((*command).IOout, "w+" );
		dup2(fileno(file_out), STDOUT_FILENO);
	}

	// executeCommand the command
	int executeCommand = execvp((*command).args[0], (*command).args);

	// Close any open file streams
	if(file_in != NULL) {
		fclose(file_in);
	}
	if(file_out != NULL) {
		fclose(file_out);
	}

	// Exit if failure to executeCommand
	if(executeCommand == -1) {
		_exit(EXIT_FAILURE);
	}
}
