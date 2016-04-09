#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
  char *algorithm;
  char *filename;
  FILE *file;
  pageInfoEntry *pageTable;   // pointer to page table, stored as an array
  pageInfoEntry *tlb;         //ignore -not being used for this assignment
  char *query;                // queries to be stored from the file referenced
  int lfu = 0; 
  int lru = 0; 

  // check for command line argument - assumes valid digit entered
  if (argc != 4){
    printf("Input Error: ");
    printf("Usage: simulator [frameRefNumber] [filename] [LRU (Least Recently Used), LFU (Least Frequently Used)]\n");
    printf("Example: 4 trace LRU\n");
    exit(0);
  }

  frames = atoi(argv[1]); // get frames
  // Check for 0 frames entered
  if(frames == 0)
  {
    printf("Frame number error: \n");
    printf("Number of frames to be used must not be 0\n"); 
    exit(0); 
  }
  filename = argv[2]; // get file name
  file = fopen(filename, "r"); // open the file
  algorithm = argv[3]; // LRU or LFU

  // deterime whether algorithm is LFU or LRU
  if(strncmp(algorithm, "LFU", 3) == 0 || strncmp(algorithm, "lfu", 3) == 0)
     lfu = 1;
  else if(strncmp(algorithm, "LRU", 3) == 0 || strncmp(algorithm, "lru", 3) == 0)
    lru = 1;
  else {
    perror("Algorithm error\n");
    printf("Indicate either LFU (Least Frequently Used) or LRU (Least Recently Used)\n");
  }
  // create space for page table entries
  pageTable = (pageInfoEntry*)malloc(frames * sizeof(pageInfoEntry));

  // Initialize defaults for page table:
  int i, j, k; 
  for(i =0; i < frames; i++)
  {
    pageTable[i].frameNumber = -1; 
    pageTable[i].lastUsed = 0; 
    pageTable[i].useCount = 0; 
  }

  // initialize page table array with entries from file
  int lineCount = 0; // number of lines in the file
  int ch;
  while(!feof(file)) {
    ch = fgetc(file);
    if(ch == '\n')
      lineCount++;
  }
  tlb = (pageInfoEntry*)malloc(lineCount * sizeof(pageInfoEntry)); 

  // initialize page table array with entries from file
  int pt = 0, q; 
  rewind(file);
  fscanf(file, "%d", &q); 
  while(!feof(file))
  {
    tlb[pt].frameNumber = q;
    tlb[pt].lastUsed = 0; 
    tlb[pt].useCount = 0;
    pt++;
    fscanf(file, "%d", &q); 
  }

  // read elements in file and check if they are in table yet
  rewind(file);
  int hit;
  while(!feof(file)) {
    fscanf(file, "%d", &q);
    hit = 0; 
    // check if frame number in table matches
    for(j = 0; j < frames; j++) {
      if(pageTable[j].frameNumber == q) {
        hit = 1;
        faults++;
        break; 
       }
    }
    if(hit != 1) {
      printf("NOTE: faults increase\n");
      //printf("");
      // check if there is an empty frame, if so put new value in
      for(i=0; i < frames; i++) {
        if(pageTable[i].useCount == 0) {
          pageTable[i].frameNumber = q;
          pageTable[i].useCount++; 
          gettimeofday(&curTime, NULL); 
          pageTable[i].lastUsed = curTime.tv_usec;
          hit = 1; 
          break;
        }
      }
      // if no empty slot (hit is still false), use lru or lfu algorithm
      if(hit != 1) {
        // Least Recently Used
        if(lru == 1) {
          //replace value which was used least recently
          int m, o = 0; 
          long double oldest = pageTable[0].lastUsed; 
          for(m=1; m < frames; m++) {
            if(pageTable[m].lastUsed < oldest) {
              oldest = pageTable[m].lastUsed;
              o = m; 
            }
          }
          pageTable[o].frameNumber = q; 
          pageTable[o].useCount = 1; 
          gettimeofday(&curTime, NULL);
          pageTable[o].lastUsed = curTime.tv_usec;
        }
        // Least Frequently Used
        else if(lfu == 1) {
          //replace least frequently used value
          int n, lu=0; 
          int leastUsed = pageTable[0].useCount;
          for(n=1; n < frames; n++) {
            if(pageTable[n].useCount < leastUsed) {
              leastUsed = pageTable[n].lastUsed;
              lu = n;
            }
          }
          pageTable[lu].frameNumber = q;
          pageTable[lu].useCount = 1;
          gettimeofday(&curTime, NULL);
          pageTable[lu].lastUsed = curTime.tv_usec;
        }
        else {
          perror("Error: lfu or lru match error\n");
        }
      }
    }
    int o;
    printf("Resultig list: ");
    for(o=0; o < frames; o++) {
      printf("%d, ", pageTable[o].frameNumber); 
    }
  }

  printf("Page faults encountered: %d\n", faults); 

  // cleanup
  close(file); 
  free(tlb); 
  free(pageTable); 
  return 0; 
}
