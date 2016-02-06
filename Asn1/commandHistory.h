#ifndef commandHistory_h
#define commandHistory_h

// Initialize command history memory storage
void init_commandHistory();

// Create space and copy command in history memory
char* create_commandhistory_entry(char* command);

// Add command to commandHistory
void add_commandhistory_entry(char* history_item);

// Print last 10 (or less) history commands (if any)
void print_commandhistory();

// Free up memory taken by history
void free_history();

#endif
