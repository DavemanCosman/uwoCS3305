/*
** This program illustrates the use of clock_gettime 
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define BILLION  1000000000L

#define CLOCK_ID CLOCK_PROCESS_CPUTIME_ID

/*Compute the difference between two time stamps returned by clock_gettime */

uint64_t diff(struct timespec start, struct timespec end)
{
  uint64_t diff;
  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
  return diff;
}

void minimalFunc(){}

/*int main(void)
{
  start = clock();
  minimalFunc();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Time taken for function call :\n%.17f\n",cpu_time_used);

  start = clock();
  getpid();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Time taken for system call :\n%.17f\n",cpu_time_used);
}*/

int main(int argc, char *argv[])
{
  start = clock():
  funcCall();
  struct timespec start, end;
  uint64_t elapsedTime;
  int i,s;

  clock_gettime(CLOCK_ID, &start);
  minimalFunc();
  clock_gettime(CLOCK_ID, &end);
  elapsedTime = diff(start,end);
  printf("elapsed process CPU time for Minimal Function Call is %llu\n",(long long unsigned int) elapsedTime);
}
