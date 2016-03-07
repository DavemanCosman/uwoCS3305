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
  pid_t pid;
    int i;

    int policy;
    struct sched_param param;
   
    if (argc != 2){
       perror("usage: comparison1 -[o = other, f = FIFO, r = Round Robin] programName \n");
       exit(0);
    }

    if (!strcmp(argv[1], "-o")) {
         policy = SCHED_OTHER;
    }
    else if(!strcmp(argv[1], "-f")){
         policy = SCHED_FIFO;
    }
    else if (!strcmp(argv[1], "-r")){
         policy = SCHED_RR;
    }
    else{
         perror("Scheduling policy not understood\n");
         exit(EXIT_FAILURE);
    }
    
    /* set process to max priority for given scheduler */
     param.sched_priority = sched_get_priority_max(policy);
    
     if(sched_setscheduler(0,policy,&param)){
         perror("Error setting scheduler policy");
         exit(EXIT_FAILURE);
     }
     
  char command[50];
  strcpy(command, argv[2]);

  while (1){
    sleep(1);
    system(command);
  }

}
