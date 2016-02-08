#ifndef commandHistory_h
#define commandHistory_h

// Initialize command history memory storage
void init_commandHistory();

// Create space and copy command in history memory
char* create_commandHistory_entry(char* command);

// Add command to commandHistory
void add_commandHistory_entry(char* history_item);

// Print last 10 (or less) history commands (if any)
void print_commandHistory();

// Free up memory taken by history
void free_commandHistory();

#endif
