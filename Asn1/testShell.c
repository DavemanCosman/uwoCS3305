#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commandType.h"
#include "constants.h"
#include "bool.h"
#include "commandParse.h"

void main (void)
{
	printf("\nHello World\n");
	char input_line[LINE_MAX];
	char* command_line = input_line;

	printf("DavidCosman> ");
	fgets(input_line, LINE_MAX, stdin);
	struct commandType command;
	command.line = command_line;
	
	commandParse (&command);
	printf("Line after Parse: %s\n", command.line);

	int i = 0;
	while (command.args[i] != NULL) {
		printf("extracted arg is %s\n", command.args[i]);
		i++;
	}
	printf("\nGoodbye World\n");

}
