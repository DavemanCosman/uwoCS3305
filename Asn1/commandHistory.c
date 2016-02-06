#include "commandHistory.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#include "arrayQueue.h"
#include "constants.h"

static Queue* history;

void init_commandHistory()
{
	init_queue (&history, MAX_HISTORY, sizeof(char) * LINE_MAX );
}

char* create_commandhistory_entry (char* command)
{
	char* history_entry = malloc(sizeof(char) * LINE_MAX);
	memcpy(history_entry, command, sizeof(char) * LINE_MAX);
	return history_entry;
}

void add_commandhistory_entry (char* history_entry)
{
	addToQueue (history, history_entry);
}

void print_commandhistory ()
{
	if ((*history).front == -1) {
		syslog (LOG_ERR, "Error: no history to display");
	}
	else {
		int history_count = MAX_HISTORY;
		char* output;
		printf("History front is %d\n",(*history).front);
		printf("History rear is %d\n",(*history).rear);
		// if there are less than 10 elements in history, decrease the history_count
		if ( ((*history).front + (*history).rear) < history_count ) {
			history_count = ((*history).front + (*history).rear);
		}
	
		// if there is only one element in history, then front == rear (both 0)
		if ((*history).front == (*history).rear) {
			output = (char*) displayQueueFront(history);
			printf("%s\n",output);
		}
		else {
			int i;
			for  (i = 0 ; i < history_count ; ++i) {
				output = (char*) displayQueueFront(history);
				printf("%s\n",output);
				(*history).front = (*history).front + 1;
				// Reset front pointer if it goes out of bounds
				if ((*history).front > history_count - 1) {
					(*history).front = 0;
				}
			}
		}
	}
}

void free_history() 
{
	free_QueueElements (history);
	free_Queue (&history);
}
