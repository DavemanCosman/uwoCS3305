/**
 * dcosmanShell.c
 * 
 * David Cosman, Feb 8th 2015
 * UWO CS 3305
 * 
 * My shell for assignment 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "commandHistory.h"
#include "commandType.h"
#include "constants.h"
#include "bool.h"

// handle signals
typedef void (*sighandler_t)(int);

// signal handler
void handle_signal(int signo) {
	fflush(stdout);
}

int main(int argc, char const *argv[])
{
	// Create input line and start command history
	char input_line[LINE_MAX];
	init_commandHistory();
	// for handling signals
	signal (SIGINT, SIG_IGN);
	signal (SIGINT, handle_signal);

	// Welcome screen with description of built in commands
	printf("/****************************************/ \n");
	printf("/* Welcome to David Cosman Shell		*/ \n");
	printf("/* exit : quit shell			*/ \n");
	printf("/* history : display last 10 commands	*/ \n");
	printf("/****************************************/ \n");
	for (;;) {
		// input prompt
		printf("\nDavidCosman> ");
		
		// Read command and give to history
		fgets(input_line, sizeof(input_line) / sizeof(char), stdin);
		
		// put history item here
		char* history_entry = create_commandHistory_entry(input_line);
		
		int input_stream = 0;			// store input stream here
		char* cmd = input_line;			// pointer to command from input_line
		char* nextPipe = strchr (cmd, '|');	// go to next piped command
		bool isFirst = true;			// bool to keep track of first command in input_line
		
		// If there are pipes, then run this:
		while ( nextPipe != NULL) {
			*nextPipe = '\0';
			struct commandType command = {
				.line = cmd,
				.firstCommand = isFirst,
				.lastCommand = false
			};
			input_stream = run (&command, input_stream);
			// go to next piped command
			cmd = nextPipe + 1;
			nextPipe = strchr(cmd, '|');
			isFirst = false;
		}
		
		// Run last command
		struct commandType command = {
			.line = cmd,
			.firstCommand = isFirst,
			.lastCommand = true
		};
		run (&command, input_stream);
		add_commandHistory_entry (history_entry);

	}
	printf("\n");
	// clean up here
	free_history();
	return EXIT_SUCCESS;
}
