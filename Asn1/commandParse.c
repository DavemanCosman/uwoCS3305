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

/*
   This function takes as input the following:
     buf: This represents the string for which the tokens are to be determined for
     tokens: This represents the array that the found tokens are tbe put into

   The function strtok() is used to find the tokens.  The delimiter used
   to distinguish tokens is a space
*/

static inline char* ignore_space (char* c) {
	while(isspace(*c))
		++c; // skip the space and move on to next character
	return c;
}

void init_info(parseInfo *p)
{
	// initialize parseInfo struct
}

// parse a single command
void parse_command (char * command, struct commandType *comm)
{
	// code to parse a single command here
}

// parse commandline for space separated commands
static void parse_cmdline (char *cmdline)
{
	cmdline = skipwhite(cmd);
	char* next = strchr(cmdline, ' ');
	int i = 0;
 
	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmdline;
		++i;
		cmdline = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}
 
	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i; 
	}
 
	args[i] = NULL;
	/* foreach cmd in cmdline {
		if (cmd == command){
			parse_command(cmd,type) }
	} */
}

// prints out parse struct
void print_info (parseInfo *info)
{
	foreach type in parseInfo {
		printf("type_name: type");
	}
}

// free the memory of parseInfo
void free_info (parseInfo *info) {
	foreach memory_block in parseInfo
		free(memory_block)
}
