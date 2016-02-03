#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
char c = '\0';

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
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	printf("\nDavidCosman> ");
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
