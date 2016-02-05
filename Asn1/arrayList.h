#ifndef arrayList_h
#define arrayList_h

#include <stddef.h>

/* arrayList
 * initializes an array list based on implementation here
 *
 * https://github.com/json-c/json-c/blob/master/arraylist.c
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 */
struct arrayList 
{
    int capacity;
    int size;
    const void** elements
};

typedef struct arrayList ArrayList;

// initializes the list to an empty list at an initial capacity
void arrayList_init (ArrayList** list, int capacity, size_t elementSize);

// adds node to back of list
void arrayListAdd (ArrayList* list, const void* node);

// deletes item at index i
void arrayListDelete (List* list, int i);

// returns item at index i
const void* getArrayListat (List* list, int i);

// frees memory used by array list
void arrayListFree( List** list );

// frees all elements in array list
void arrayListFreeAll( List* list );

#endif
