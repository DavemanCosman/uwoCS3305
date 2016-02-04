#ifndef parser_h
#define parser_h

#include "bool.h"
#include "commandType.h"

// parse commandline for space separated commands
void parse_tokens (char *buf, struct commandType* comm);

#endif
