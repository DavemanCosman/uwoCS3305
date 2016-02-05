#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	char* command_line = input_line;
	
	// initalize history here
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
		fgets(input_line, LINE_MAX, stdin);
		// put history item here
		
		command.line = command_line;
		commandParse (&command);
	}
	printf("\n");
	// clean up here
	return 0;
}
