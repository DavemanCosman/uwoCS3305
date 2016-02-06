#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commandHistory.h"
#include "commandType.h"
#include "constants.h"
#include "commandParse.h"
#include "bool.h"

typedef void (*sighandler_t)(int);

void handle_signal(int signo)
{
	printf("\nDavidCosman> ");
	fflush(stdout);
}

void fill_argv(char *tmp_argv)
{
	char *foo = tmp_argv;
	int index = 0;
	char ret[100];
}

int main(int argc, char const *argv[])
{
	char input_line[LINE_MAX];
	init_commandhistory();
	struct commandType command;

	printf("/****************************************/ \n");
	printf("/* Welcome to Dcosman Shell		*/ \n");
	printf("/* exit : quit shell			*/ \n");
	printf("/* history : display last 10 commands	*/ \n");
	printf("/****************************************/ \n");
	for (;;) {
		// Prompt
		printf("\nDavidCosman> ");
		
		// Read command and give to history
		fgets(input_line, sizeof(input_line) / sizeof(char), stdin);
		
		// put history item here
		char* history_entry = create_commandhistory_entry(input_line);
		
		int input_stream = 0;			// store input stream here
		char* cmd = input_line;			// get command from input line
		char* nextPipe = strchr (cmd, '|');	// go to next pipe
		
		while ( nextPipe != NULL) {
			*nextPipe = '\0';
			command.line = cmd;
			// execute commands here and include the bottom part (?)
			commandParse (&command);
			print_tokens (&command);
		}
		
		// Run last command
		command.line = cmd;
		// execute command here and include the bottom part (?)
		commandParse (&command);
		print_tokens (&command);
		
		add_commandhistory_entry (history_entry);
		printf("\ncommand history:\n");
		print_commandhistory();
	}
	printf("\n");
	// clean up here
	return 0;
}
