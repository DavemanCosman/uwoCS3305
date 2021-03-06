#ifndef queueList_h
#define queueList_h

#include <stddef.h>
#include "bool.h"

/* arrayQueue
 * Implement a circular queue using an array
 */
struct arrayQueue
{
	// rear and front node indexes. -1 if empty
	int rear; // Rear also represents the current size. 
	int front;
	// Max size of the queue
	int max_capacity;
	// The array of elements in the queue
	const void** queue_elements;
	// to determine if size has already passed max
	bool size;
};

typedef struct arrayQueue Queue;

// initializes queue; sets it empty at an initial capacity
void init_queue (Queue** queue, int capacity, size_t elementSize);

// adds node to back of queue
void addToQueue (Queue* queue, const void* node);

// deletes front item from queue
void removeFromQueue (Queue* queue);

// returns the front element in the queue
const void* displayQueueFront (Queue* queue);

// frees memory used by array queue
void free_Queue(Queue** queue);

// frees all elements in array queue
void free_QueueElements(Queue* queue);

#endif
