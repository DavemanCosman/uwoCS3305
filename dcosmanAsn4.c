#include <errno.h>
#include <sys/types.h>
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
  int i, j, o;
  int frames;
  char *algorithm;
  char *filename;
  FILE *file;
  pageInfoEntry *pageTable;   // pointer to page table, stored as an array
  pageInfoEntry *tlb;         // TLB, now just used to store the contents of the file
  int lfu = 0, lru = 0;

  // check for command line argument - assumes valid digit entered
  if (argc != 4){
    printf("usage: ./simulator [frameRefNumber] [filename] [LRU | LFU]\n");
    printf("example: 4 foo LRU\n");
    exit(0);
  }

  // Get frames entered
  frames = atoi(argv[1]);
  if(frames == 0) {
    perror("Frame error");
    printf("Number of frames must not be 0\n"); 
    return(-1); 
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
    perror("Incorrect argument;\nIndicate either LFU (Least Frequently Used) or LRU (Least Recently Used)\n");
    return 22;
  }
  // create space for page table entries
  pageTable = (pageInfoEntry*)malloc(frames * sizeof(pageInfoEntry));

  // Initialize defaults for page table:
  for(i = 0; i < 0; i++)
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
  while(!feof(file))
  {
    fscanf(file, "%d", &q); 
    printf("scanning file: q = %d", q);
    tlb[pt].frameNumber = q;
    tlb[pt].lastUsed = 0; 
    tlb[pt].useCount = 0;
    pt++;
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
        break; 
       }
    }
    if(hit != 1) {
      faults++;
      printf("! ");
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
          printf("ERROR: Algorithm not reached.\n");
        }
      }
    }
    printf("\nResulting list: ");
    for(o = 0; o < frames; o++) {
      printf("%d, ", pageTable[o].frameNumber); 
    }
  }

  printf("\nPage faults encountered: %d\n", faults); 

  // cleanup
  close(file); 
  free(tlb); 
  free(pageTable); 
  return 0; 
}
