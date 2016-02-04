#ifndef parser_h
#define parser_h

#include "bool.h"
#include "commandType.h"

// parse commandline for space separated commands
void commandParse (struct commandType* command);

// used for testing to print tokens
void print_tokens (struct commandType* command)

#endif
