#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int policy;
    struct sched_param param;
   
    if (argc != 3){
       perror("usage: comparison1 -[o = other, f = FIFO, r = Round Robin] programName \n");
       exit(0);
    }
    
  char* setPolicy = argv[1];
  char command[50];
  strcpy(command, argv[2]);
  printf("comparing program %s \n", command);

    if (strcmp(setPolicy, "-o")==0) {
         policy = SCHED_OTHER;
         printf("policy set to Other %d \n", policy);
    }
    else if(strcmp(setPolicy, "-f")==0){
         policy = SCHED_FIFO;
         printf("policy set to FIFO %d \n", policy);
    }
    else if (strcmp(setPolicy, "-r")==0){
         policy = SCHED_RR;
         printf("policy set to RR %d \n", policy);
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

  while (1){
    sleep(1);
    system(command);
  }

}
