#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(int argc, char *argv[])
{
  if (argc != 2){
       perror("incorrect arguments");
       exit(0);
    }
  
  char command[50];
  strcpy(command, argv[1]);

  while (1){
    sleep(1);
    system(command);
  }

}
