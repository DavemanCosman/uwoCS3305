#include "arrayQueue.h"
#include "bool.h"

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

/* init_queue
 * Initlaizes queue
 * - queue: the queue
 * - capacity: amount of elements it can hold (Default: 10)
 * - elementSize: used to allocate memory for items
 */
void init_queue (Queue** queue, int capacity, size_t elementSize)
{
	Queue* new_queue = malloc(sizeof(Queue));
	(*new_queue).rear = (*new_queue).front = -1;
	(*new_queue).queue_elements = malloc(capacity * elementSize);
	(*new_queue).max_capacity = capacity;
	(*new_queue).size = false;
	*queue = new_queue;
}

/* addToQueue
 * Adds node to back of queue
 * - queue: the queue being added to
 * - node: the node being added
 */
void addToQueue (Queue* queue, const void* node)
{
	// Check if there are already max capacity items
	if ( ((*queue).front + (*queue).rear) == ((*queue).max_capacity - 1) ) {
		(*queue).size = true;
	}
	// Remove the front from the queue if max capacity has been reached
	if ((*queue).size == true) {
		removeFromQueue(queue);
	}
	// If queue is initially empty, set index of first element to 0 in array queue
	if ((*queue).front == -1) {
		(*queue).front = 0;
	}
	// Increase the rear index by one and add element
	(*queue).rear = (*queue).rear + 1;
	(*queue).queue_elements[(*queue).rear] = node;
}

/* removeFromQueue
 * Delete front item from queueu and adjust front and rear pointers
 * - queue: the queue being deleted from
 */
void removeFromQueue (Queue* queue) 
{
	// No items in queue: throw error and exit
	if ((*queue).front == -1) {
		syslog (LOG_ERR, "Error: queue underflow\n");
		return;
	}
	else {
		// If rear poins to the tail of arrayQueue, then front must be at index 0
		if ((*queue).rear == ((*queue).max_capacity - 1)) {
			// point queue rear to position before front's position
			(*queue).rear = (*queue).front - 1;
		}
		// increase front index by 1
		(*queue).front = (*queue).front + 1;
		// if front index exceeds max capacity, reset front index to start of arrayQueue:
		if ((*queue).front > (*queue).max_capacity - 1) {
			(*queue).front = 0;
		}
	}
	/* removeFromQueue will usually only be ran by:
	 * - addToQueue, which will add the element in rear+1 index
	 * - free_QueueElements, which will get the front element, remove it,
	 *   and free the memory used by that element. It will continue until it
	 *   reaches the end of the queue.
	 */
}

/* displayQueueFront
 * display the front item int the queue given
 * queue: given queue
 */
const void* displayQueueFront (Queue* queue)
{
	int i;
	if ((*queue).front == -1) {
		syslog (LOG_ERR, "Error: empty queue\n");
		return NULL;
	}
	return (*queue).queue_elements[(*queue).front];
}

/* free_Queue
 * free up memory used by arrayQueue
 * queue: the queue being freed
 */
void free_Queue (Queue** queue)
{
	free((*queue)->queue_elements );
	free(*queue);
}

/* free_QueueElements
 * free up memory used by arrayQueue elements
 * queue: the queue being freed
 */
void free_QueueElements (Queue* queue)
{
	int i;
	for (i = 0; i < (*queue).max_capacity; ++i ) {
		void* element  = (void*) displayQueueFront(queue);
		removeFromQueue(queue);
		free(element);
	}
}
