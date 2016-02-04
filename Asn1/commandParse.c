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
 * Skip whitespaces, such as ' ' or escape chars '\n'
 * See: http://www.tutorialspoint.com/c_standard_library/c_function_isspace.htm
 */
 static char* skipwhite( char* s )
 {
	while( isspace( *s ) ) ++s;
	return s;
 	
 }
 
/*
 * Only the parser idea was taken from simple shell example here:
 * https://gist.github.com/parse/966049
 * See split() method
 *
 * commandType structure was created for ease of access and for built in commands.
 */
void commandParse (struct commandType* command)
{
	/* pseudo code
	--
	foreach cmd in cmdline {
		if (cmd == command) {
			parse_command(cmd, type)
      }
      */
      
	// pointer to the entire command in commandType, to be split into tokens
	char* cmd = command.command;		// token being read
	int token_count = 0;			// keeps track of number of tokens
	bool nextIOin, nextIOout = false;	// for IO redirection

	cmd = skipwhite(t, ' ');		// ignoring whitespaces
	char* next = strchr( cmd, ' ' );	// to skip to the next command

	while (next != NULL) {
		next[0] = '\0';
		// continue: http://www.tutorialspoint.com/cprogramming/c_continue_statement.htm
		
		// When the next token is '>', then next token is outstream
		if (strcmp(cmd, ">") == 0) {
			nextIOout = true;
			cmd = skipwhite(next+1);
			next = strtchr(cmd, ' ');
			continue;
		}
		// When the next token is '<', then next token is outstream
		if (strcmp(cmd, "<") == 0) {
			nextIOin = true;
			cmd = skipwhite(next+1);
			next = strtchr(cmd, ' ');
			continue;
		}
		
		// Sets internal commandType io values and resets bools
		if (nextIOout == true) {
			command.IOout = cmd;
			nextIOout = false;
		}
		else if (nextIOin == true) {
			command.IOin = cmd;
			nextIOin = false;
		}
		// Adds the token to the list of args otherwise
		else {
			command.args[n] = cmd;
			++token_count;
		}
		cmd = skipwhite(next+1);
		next = strchr(token, ' ');
	}
	
	// If last argument, interpret it
	if (cmd[0] != '\0')
		// Sets internal commandType io values and resets bools
		if (nextIOout == true) {
			command.IOout = cmd;
			nextIOout = false;
		}
		else if (nextIOin == true) {
			command.IOin = cmd;
			nextIOin = false;
		}
		// Adds the token to the list of args otherwise
		else {
			command.args[n] = cmd;
			++token_count;
		}
		
		next = strchr(cmd,'\n');
		next[0] = '\0';
		++token_count;
	}
	
	// Set end of args list to NULL
	command.args[n]=NULL;
}
