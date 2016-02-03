#ifndef parser_h
#define parser_h

#include "bool.h"
#include "command.h"

// Parses a command, generating its arguments list 
// and storing any IO redirection parameters as well
void parse_tokens(char *buf, char *tokens[]);

// parse a single command
void parse_command (char * token, struct commandType *comm);

#endif
