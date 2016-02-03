#ifndef parser_h
#define parser_h

#include "bool.h"
#include "commandType.h"

// parse a single command
void parse_command (char * token, struct commandType *comm);

// parse commandline for space separated commands
void parse_tokens(char *buf, char *tokens[]);

#endif
