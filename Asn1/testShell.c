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
	char input_line[LINE_MAX];
	char* command_line = input_line;

	printf("DavidCosman> ");
	fgets(input_line, LINE_MAX, stdin);
	struct commandType command;
	command.line = command_line;
	
	commandParse (&command);
	print_tokens(&command);
}
