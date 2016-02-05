#include "arrayQueue.h"

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

void init_queue (Queue** queue, int capacity, size_t elementSize)
{
	Queue* new_queue = malloc(sizeof(Queue));
	(*new_queue).rear = (*new_queue).front = -1;
	(*new_queue).queue_elements = malloc(capacity * elementSize);
	(*new_queue).max_capacity = capacity;
	*queue = new_queue;
}

void addToQueue (Queue* queue, const void* node)
{
	// Check if there are already 10 items.
	if ( ((*queue).front + (*queue).rear) == ((*queue).max_capacity - 1) ) {
		// If there are, remove the front from the queue
		removeFromQueue(queue);
	}
	// If queue is initially empty, set index of first element to 0 in array queue
	if ((*queue).front == -1) {
		(*queue).front = 0;
	}
	(*queue).rear = (*queue).rear + 1;
	(*queue).queue_elements[(*queue).rear] = node;
}

void removeFromQueue (Queue* queue) 
{
	if ((*queue).front == -1 || (*queue).front > (*queue).rear) {
		printf("Fatal error: Queue underflow\n");
		return;
	}
	else {
		if ((*queue).rear == ((*queue).max_capacity - 1)) {
			// point queue rear to position before front's position
			(*queue).rear = (*queue).front - 1;
		}
		// increase index by 1
		(*queue).front = (*queue).front + 1;
		// if it comes full circle on queue:
		if ((*queue).front > (*queue).max_capacity - 1) {
			(*queue).front = (*queue).rear;
		}
	}
}

const void* displayQueueFront (Queue* queue)
{
	int i;
	if ((*queue).front == -1) {
		syslog (LOG_ERR, "Error: empty queue\n");
		return NULL;
	}
	return (*queue).queue_elements[(*queue).front];
}

void free_Queue (Queue** queue)
{
	free((*queue)->elements );
	free(*queue);
}

void free_QueueElements (Queue* queue)
{
	int i;
	for (i = 0; i < (*queue).max_capacity; ++i ) {
		void* element  = (void*) displayQueueFront(queue);
		removeFromQueue(queue);
		if ((*queue).front > (*queue).max_capacity - 1) {
			(*queue).front = 0;
		}
		free(element);
	}
}
