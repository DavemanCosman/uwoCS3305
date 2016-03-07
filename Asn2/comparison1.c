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
  pid_t pid;
    int i;
    int policy;
    struct sched_param param;
   
    if (argc < 3){
       perror("usage: comparison1 -[o = other, f = FIFO, r = Round Robin] programName \n");
       exit(0);
    }
    
  char* setPolicy = argv[1];
  char command[50];
  for (i=2; i<sizeof(argv) ; i++){
    strcat(command, argv[i]);
  }

    if (strcmp(setPolicy, "-o")==0) {
         policy = SCHED_OTHER;
    }
    else if(strcmp(setPolicy, "-f")==0){
         policy = SCHED_FIFO;
    }
    else if (strcmp(setPolicy, "-r")==0){
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

  while (1){
    sleep(1);
    system(command);
  }

}
