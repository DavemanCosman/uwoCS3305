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
#include "arrayQueue.h"

static Queue* history;

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
	init_queue (&history, MAX_HISTORY , sizeof(char) * LINE_MAX);
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
		fgets(input_line, sizeof(line) / sizeof(char), stdin);
		
		// put history item here
		char* history_item = malloc(sizeof(char)*LINE_MAX);
		memcpy(history_item,command,sizeof(char)*LINE_MAX);
		
		// To do: read pipe | delimeters here and separate by them
		
		// execute commands here and include the bottom part (?)
		command.line = &input_line;
		commandParse (&command);
		
		// execute commands here (?)
		
		addToQueue(history, history_item);
		printf("%s\n", displayQueueFront(queue));
	}
	printf("\n");
	// clean up here
	return 0;
}
