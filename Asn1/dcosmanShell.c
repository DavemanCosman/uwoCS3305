#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "command.h"
#include "constants.h"

typedef void (*sighandler_t)(int);

// Array will hold arguments
static char* args[MAX_CMD];

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
	char input_line[MAX];
	int i, n;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	
	printf("\nDavidCosman> ");
	if (fgets(input_line, MAX, stdin) != NULL)
		n = make_tokenlist(input_line, tokens);
	else
		printf("Command not found\n");
	while(c != EOF) {
		c = getchar();
		switch(c) {
			case '\n': /* parse and execute */
				bzero(tmp, sizeof(tmp));
				break;
			default: strncat(tmp, &c, 1);
				break;
		}
		printf("DavidCosman> ");
	}
	printf("\n");
	return 0;
}
