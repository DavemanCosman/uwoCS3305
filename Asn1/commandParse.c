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

/*
 * Parse commandline for space separated commands
 *
 * Based on token parser example in CS 3305 by Hannan Lutfiya
 * This function was modified;
 * 	- The command structure was implemented to save space. comm.command is *buf
 * 	- tokens: This represents the array that the found tokens are put into. Localized.
 * 	- The function strtok() is used to find the tokens; the delimiter used to distinguish tokens is a space
 */
void parse_tokens(struct commandType* comm)
{
	/* pseudo code
	--
	foreach cmd in cmdline {
		if (cmd == command) {
			parse_command(cmd, type)
      }
      */
      
	// pointer to the entire command in commandType, to be split into tokens
	char* line = comm.command;	// line being read
	char tokens[];			// list of tokens
	int i,n = 0;
	bool nextIOin, nextIOout = false;

	tokens[i] = strtok(line, " "); // pass tokens ignoring spaces
	do {
		i++;
		line = NULL;
		tokens[i] = strtok(line, " ");
		
		// If redirecting out, next token is instream
		if (strcmp(tokens[i], ">") == 0) {
			nextIOout = true;
			tokens[i] = strtok(line, " ");
			continue;
		}
		
		// If redirect in, next token is outstream
		if (strcmp(tokens[i], "<") == 0) {
			nextIOin = true;
			tokens[i] = strtok(line, " ");
			continue;
		}
		
		if (nextIOout == true)
		{
			comm.IOout = tokens[i];
			nextIOout = false;
		}
		else if (nextIOin == true)
		{
			comm.IOin = tokens[i];
			nextIOin = false;
		}
		else
		{
			comm.args[n] = tokens[i];
			++n;
		}
		
		tokens[i] = strtok(line, " ");
	} while(tokens[i] != NULL);
	
	// indicate end of args list
	comm.args[n]=NULL;
}
