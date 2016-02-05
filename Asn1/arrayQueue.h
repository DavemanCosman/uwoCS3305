#ifndef queueList_h
#define queueList_h

#include <stddef.h>

/* arrayQueue
 * Implement a circular queue using an array
 */
struct arrayQueue
{
	// rear and front node indexes
	int rear = -1; // Rear also represents the current size. -1 if empty
	int front = -1;
	// Max size of the queue
	int max_capacity;
	// The array of elements in the queue
	const void** queue_elements;
}

typedef struct arrayQueue Queue;

// initializes queue; sets it empty at an initial capacity
void init_queue (Queue** queue, int capacity, size_t elementSize);

// adds node to back of queue
void addToQueue (Queue* queue, const void* node);

// deletes front item from queue
void removeFromQueue (Queue* queue);

// returns the queue array of elements
const void* displayQueue (Queue* list);

// frees memory used by array queue
void free_Queue(Queue** list);

// frees all elements in array queue
void free_QueueElements(Queue* list);

#endif
