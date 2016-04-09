#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef enum { false, true } bool;
// File structure for page reference
typedef struct pageInfo
{
  int frameNumber; 
  time_t lastUsed; //change to time of day
  int useCount; 
} pageInfoEntry;

// Global variables
int faults = 0; // to store faults found
struct timeval curTime; // represents real time for lastUsed

/* Method: main
 * Memory Trace simulator
 *
 * Accepted arguments:
 * - frames used on simulation
 * - file name with memory trace (page references vary: 0 to 1023)
 * - LRU (Least Recently Used), LFU (Least Frequently Used)
 *
 * NOTE: TLB not included in asn, ignore references to it
 */
int main(int argc, char** argv) 
{
  int frames;
  bool hit;
  char *algorithm;
  char *filename;
  FILE *file;
  pageInfoEntry *pageTable;   // pointer to page table, stored as an array
  pageInfoEntry *tlb;         // TLB, now just used to store the contents of the file
  bool lfu = false;
  bool lru = false;

  // check for command line argument - assumes valid digit entered
  if (argc != 4){
    printf("usage: ./simulator [frameRefNumber] [filename] [LRU | LFU]\n");
    printf("example: 4 trace LRU\n");
    exit(0);
  }

  // Get frames entered
  frames = atoi(argv[1]);
  if(frames <= 0) {
      printf("Frame error: Number of frames must be greater than 0\n");
      return(-1);
    }
  // create space for page table entries and initialize defaults
  pageTable = (pageInfoEntry*)malloc(sizeof(pageInfoEntry)*frames);
  int i;
  for(i = 0; i < frames; i++) {
    pageTable[i].frameNumber = -1;
    pageTable[i].lastUsed = 0;
    pageTable[i].useCount = 0; 
  }
  
  // Get file location
  filename = argv[2];
  file = fopen(filename, "r");
  if (file == NULL) {
    perror("File error");
    return(-1);
  }
  
  // deterime whether algorithm is LFU or LRU
  algorithm = argv[3]; // LRU or LF
  if(strncmp(algorithm, "LFU", 3) == 0 || strncmp(algorithm, "lfu", 3) == 0)
     lfu = true;
  else if(strncmp(algorithm, "LRU", 3) == 0 || strncmp(algorithm, "lru", 3) == 0)
    lru = true;
  else {
    printf("Incorrect argument: %s\n", algorithm);
    printf("usage: ./simulator [frameRefNumber] [filename] [LRU | LFU]\n");
    printf("example: 4 trace LRU\n");
    return -1;
  }

  // initialize TLB array with entries from file
  int c;
  int lineCount = 0; // number of lines in the file
  while(!feof(file)) {
    c = fgetc(file);
    if(c == '\n')
      lineCount++;
  }
  tlb = (pageInfoEntry*)malloc(lineCount * sizeof(pageInfoEntry)); 
  int j = 0, q;
  rewind(file);
  while(!feof(file) && j < lineCount)
  {
    fscanf(file, "%d", &q); 
    printf("scanning frame number: %d\n", q); // Problem here, last num duplicated.
    tlb[j].frameNumber = q;
    tlb[j].lastUsed = 0; 
    tlb[j].useCount = 0;
    j++;
  }

  // read elements in file and check if they are in table yet
  rewind(file);
  int k = 0;
  while(!feof(file) && k < lineCount) {
    fscanf(file, "%d", &q);
    hit = false; 
    // check if frame number in table matches or if empty slot exists
    for(i = 0; i < frames; i++) {
      if(pageTable[i].frameNumber == q || pageTable[i].useCount == 0) {
        pageTable[i].frameNumber = q;
        if (pageTable[i].useCount == 0) {
          faults++; // fault found if number of uses was 0 (null)
          printf("\nFound a fault"); }
        else { printf("\nFound a hit"); }
        pageTable[i].useCount++;
        gettimeofday(&curTime, NULL); 
        pageTable[i].lastUsed = curTime.tv_usec;
        hit = true;
        break;
       }
    }
    // check if item was inserted into page table
    if(hit == false) {
      faults++;
      printf("\nFound a fault");
      // Least Recently Used
      if(lru == true) {
        printf("\nusing LRU");
        //replace value which was used least recently
        int o = 0; 
        long double oldest = pageTable[0].lastUsed; 
        for(j=1; j < frames; j++) {
          if(pageTable[j].lastUsed < oldest) {
            oldest = pageTable[j].lastUsed;
            o = j;
          }
        }
        pageTable[o].frameNumber = q; 
        pageTable[o].useCount = 1; 
        gettimeofday(&curTime, NULL);
        pageTable[o].lastUsed = curTime.tv_usec;
      }
      // Least Frequently Used
      else if(lfu == true) {
        printf("\nusing LFU");
        //replace least frequently used value
        int lu=0; 
        int leastUsed = pageTable[0].useCount;
        for(j=1; j < frames; j++) {
          if(pageTable[j].useCount < leastUsed) {
            leastUsed = pageTable[j].lastUsed;
            lu = j;
          }
        }
        pageTable[lu].frameNumber = q;
        pageTable[lu].useCount = 1;
        gettimeofday(&curTime, NULL);
        pageTable[lu].lastUsed = curTime.tv_usec;
      }
      else {
        printf("ERROR: Algorithm not reached.\n"); }
    }
    printf("\nResulting list: ");
    for(i = 0; i < frames; i++) {
      printf("%d, ", pageTable[i].frameNumber); }
    k++;
  }

  printf("\nPage faults encountered: %d\n", faults);
  perror("Any errors");

  // cleanup
  close(file); 
  free(tlb); 
  free(pageTable); 
  return 0; 
}
