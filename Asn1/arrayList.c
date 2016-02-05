#include "arrayList.h"

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

void arrayList_init (ArrayList** list, int capacity, size_t elementSize)
{

	ArrayList* newList = malloc(sizeof(List));
	(*newList).elements = malloc(capacity * elementSize);
	(*newList).capacity = capacity;
	(*newList).size = 0;
	*list = newList;
}

void arrayListAdd (ArrayList* list, const void* node ) 
{
	if((*list).capacity == (*list).size ) {
		// delete last item in history before adding
		arrayListDelete (list, capacity-1);
	}
	(*list).elements[(*list).size] = item;
	++((*list).size);
}

void arrayListDelete( List* list, int index ) 
{
	// Move over and unlink last item
	int i;
	for (i = index; i < (*list).size; ++i)
		(*list).elements[i] = (*list).elements[i+1];
	
	--((*list).size);
}

const void* getArrayListAt(List* list, int index)
{
	if(index >= (*list).size) {
		syslog( LOG_ERR, "Fatal error: list given invalid index; %d\n", index );
		return NULL;
	}
	return (*list).elements[index];
}

void arrayListFree(List** list)
{
	free((*list)->elements );
	free(*list);
}

void arrayListFreeAll( List* list )
{
	int i;
	for( i = 0; i < (*list).size; ++i ) {
		void* element  = (void*) getArrayListAt(list, i);
		free(element);
	}
}
