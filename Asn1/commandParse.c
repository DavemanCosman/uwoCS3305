/**
 * commandParse.c
 * 
 * David Cosman, Feb 3rd 2015
 * UWO CS 3305
 * 
 * A basic command parser
 */
 
#include "commandParse.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commandType.h"
#include "constants.h"
#include "bool.h"

/*
 * Skip whitespaces, such as ' ' or escape chars '\n'
 * See: http://www.tutorialspoint.com/c_standard_library/c_function_isspace.htm
 */
 static char* skipwhite(char* s)
 {
	while (isspace(*s)) {
		++s; }
	return s;
 	
 }
 
/*
 * Only the parser idea was taken from simple shell example here:
 * https://gist.github.com/parse/966049
 * See split() method
 *
 * commandType structure was created for ease of access and for built in commands.
 * Structure idea taken from cornell.edu pseudo code;
 * Shell: http://www.cs.cornell.edu/Courses/cs414/2004su/homework/shell/shell.html
 * Parser: http://www.cs.cornell.edu/Courses/cs414/2004su/homework/shell/parse.html
 *
 * continue: http://www.tutorialspoint.com/cprogramming/c_continue_statement.htm
 */
void commandParse (struct commandType* command)
{
	char* cmd = (*command).line;		// line read to be parsed into tokens
	bool nextIOin, nextIOout = false;	// for IO redirection

	cmd = skipwhite(cmd);			// ignoring whitespaces
	char* next = strchr( cmd, ' ' );	// to skip to the next command
	int token_count = 0;			// keeps track of number of tokens, used for argument storage

	while (next != NULL) {
		next[0] = '\0';
		// When the next token is '>', then next token is outstream
		if (strcmp(cmd, ">") == 0) {
			nextIOout = true;
			cmd = skipwhite(next+1);
			next = strchr(cmd, ' ');
			continue;
		}
		// When the next token is '<', then next token is outstream
		if (strcmp(cmd, "<") == 0) {
			nextIOin = true;
			cmd = skipwhite(next+1);
			next = strchr(cmd, ' ');
			continue;
		}
		
		// Sets internal commandType io values and resets bools
		if (nextIOout == true) {
			(*command).IOout = cmd;
			nextIOout = false;
		}
		else if (nextIOin == true) {
			(*command).IOin = cmd;
			nextIOin = false;
		}
		// Adds the token to the list of args otherwise
		else {
			(*command).args[token_count] = cmd;
			++token_count;
		}
		cmd = skipwhite(next+1);
		next = strchr(cmd, ' ');
	}
	
	// If last argument, interpret it
	if (cmd[0] != '\0') {
		// Sets internal commandType io values and resets bools
		if (nextIOout == true) {
			(*command).IOout = cmd;
			nextIOout = false;
		}
		else if (nextIOin == true) {
			(*command).IOin = cmd;
			nextIOin = false;
		}
		// Adds the token to the list of args otherwise
		else {
			(*command).args[token_count] = cmd;
			++token_count;
		}
		
		next = strchr(cmd,'\n');
		next[0] = '\0';
		++token_count;
	}
	
	// Set end of args list to NULL
	(*command).args[token_count] = NULL;
}

void print_tokens (struct commandType* command)
{
	if ((*command).line!=NULL) {
		int i = 0;
		while ((*command).args[i] != NULL) {
			printf("extracted arg is %s\n", (*command).args[i]);
			i++;
		}
	}
	else{
		printf("\nFatal error: NULL command given.\n");
	}
}
