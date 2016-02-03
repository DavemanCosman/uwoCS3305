#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAX 256
#define CMD_MAX 10

typedef void (*sighandler_t)(int);
char c = '\0';

/*
   This function takes as input the following:
   	buf: This represents the string for which the tokens are to be determined for.
   	tokens: This represents the array that the found tokens are tbe put into.

   The function strtok() is used to find the tokens.  The delimiter used to distinguish 
   tokens is a space.
*/

int make_tokenlist(char *buf, char *tokens[])
{

 char input_line[MAX];
 char *line;
 int i,n;

 i = 0;

 line = buf;
 tokens[i] = strtok(line, " ");
 do  {
    i++;
    line = NULL;
    tokens[i] = strtok(line, " ");
 } while(tokens[i] != NULL);

 return i;
}

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

int main(int argc, char *argv[], char *envp[])
{
	char input_line[MAX], *tokens[CMD_MAX];
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
