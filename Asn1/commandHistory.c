#include "commandHistory.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#include "arrayQueue.h"
#include "constants.h"
#include "bool.h"

static Queue* history;

void init_commandHistory()
{
	init_queue (&history, MAX_HISTORY, sizeof(char) * LINE_MAX );
}

char* create_commandHistory_entry (char* command)
{
	char* history_entry = malloc(sizeof(char) * LINE_MAX);
	memcpy(history_entry, command, sizeof(char) * LINE_MAX);
	return history_entry;
}

void add_commandHistory_entry (char* history_entry)
{
	addToQueue (history, history_entry);
}

void print_commandHistory ()
{
	if ((*history).front == -1) {
		syslog (LOG_ERR, "Error: no history to display");
	}
	else {
		int history_count = MAX_HISTORY;
		char* output;
		// if there are less than max elements in history, decrease the history_count
		if ((*history).size == false ) {
			history_count = (*history).rear + 1;
		}
	
		// if there is only one element in history, then front == rear (both 0)
		if ((*history).front == (*history).rear) {
			output = (char*) displayQueueFront(history);
			printf("%s",output);
		}
		else {
			int i;
			for  (i = 0 ; i < history_count ; ++i) {
				output = (char*) displayQueueFront(history);
				printf("%s",output);
				(*history).front = (*history).front + 1;
				// Reset front pointer if it goes out of bounds
				if ((*history).front > history_count - 1) {
					(*history).front = 0;
				}
			}
		}
	}
}

void free_commandHistory() 
{
	free_QueueElements (history);
	free_Queue (&history);
}
