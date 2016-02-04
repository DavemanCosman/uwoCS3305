/**
 * commandParse.c
 * 
 * David Cosman, Feb 3rd 2015
 * UWO CS 3305
 * 
 * A basic command parser
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "commandParse.h"
#include "constants.h"

#define MAX 256
#define CMD_MAX 10

/*
static inline char* ignore_space (char* c) {
	while(isspace(*c))
		++c; // skip the space and move on to next character
	return c;
}*/

// parse a single command
void parse_command (char *token, struct commandType *comm)
{
	// code to parse a single command here
}

/*
 * Parse commandline for space separated commands
 *
 * Taken from assignment token parser example in CS 3305 by Hannan Lutfiya
 * This function takes as input the following:
 * 	- buf: This represents the string for which the tokens are to be determined for.
 * 	- tokens: This represents the array that the found tokens are put into.
 * 	- The function strtok() is used to find the tokens.
 * The delimiter used to distinguish tokens is a space
 */
void parse_tokens(char *buf, char *tokens[])
{
	/*foreach cmd in cmdline {
      if (cmd == command) {
        parse_command(cmd, type)
      }*/
	char input_line[MAX];
	char *line;
	int i,n;
	
	bool IOin, IOout = false;

	i = 0;
	line = buf;
	tokens[i] = strtok(line, " ");
	do {
		i++;
		line = NULL;
		tokens[i] = strtok(line, " ");
	} while(tokens[i] != NULL);
	
	n=i;
	for (i = 0; i < n; i++)
	{
		
		// printf("extracted token is %s\n", tokens[i]);
		if (strcmp(token[i], "<") == 0)
			IOin = true;
		if (strcmp(token[i], ">") == 0)
			IOout = true;
	}
}

/* prints out parse struct
void print_tokens (char *tokens [])
{
	char input_line[MAX], *tokens[CMD_MAX];
	int i, n;
	
	printf("hanan> ");
	if (fgets(input_line,MAX,stdin) != NULL)
		n= make_tokenlist(input_line, tokens);
	else
		printf("huh?\n");

	for (i = 0; i < n; i++)
		printf("extracted token is %s\n", tokens[i]);
}*/
