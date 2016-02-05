#ifndef commandhistory_h
#define commandhistory_h

// Initialize command history memory storage
void commandhistoryInit();

// Create space and copy command in history memory
char* commandToHistory(char* command);

// Add command to commandHistory
void historyAdd(char* history_item);

// Print last 10 (or less) history commands (if any)
void historyPrintLast(int count);

// Free up memory taken by history
void historyFree();

#endif
