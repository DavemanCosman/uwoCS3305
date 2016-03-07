#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

void handle_signal (int signo) {
	fflush(stdout);
}

int main(int argc, char **argv)
{
	// Check argc, should be 2 for proper execution 
	if ( argc != 2 ) {
		printf( "usage: %s filename", argv[0] );
  }
  // Allocate memory for pidof and point to the command
	char *st = (char*)malloc(sizeof(char)*256);
	strcat(st, "pidof ");
	strcat(st, argv[1]);
	printf("Test st: %s \n", st);

	// Execute command as subprocess
	char line[strlen(st)];
  	FILE *executable = popen(argv[1], "r");
	FILE *cmd = popen(st, "r");
	fgets(line, strlen(st), cmd);
	// get pid of process
	pid_t pid = strtoul(line, NULL, 10);
	pclose(cmd);
	
	// Allocate memory for proc
	char *str = (char*)malloc(sizeof(char)*256);
	strcat(str, "/proc/");
	char s[15];
	sprintf(s, "%d", pid);
	// concatenate pid and the /stat path
	strcat(str, s);
	strcat(str, "/stat");
	printf("Test str: %s \n", str);
	
	// start observing
	while(1) {
		FILE *cpuinfo = NULL;						
		cpuinfo = fopen(str, "rb");		
		char buffer[502] = {0};						
		fread(buffer, 500, 1, cpuinfo);   			
		
		// count of buffer length
		int count = 0;
		int i;
		for (i = 0; i < strlen(buffer); i++) {
			if (buffer[i] == ' ') {
		  	count++; }
		}
	  	
		int j;
		char *p;
		char *array[count];
		j = 0;
		p = strtok (buffer," ");  
		while (p != NULL) {
			array[j++] = p;
			p = strtok (NULL, " ");
		}
		int l = atol(array[13]);
		int m = atol(array[14]);
		printf("utime = %ld\r\n", l/sysconf(_SC_CLK_TCK));
		printf("stime = %ld\r\n", m/sysconf(_SC_CLK_TCK));
		sleep(5);
		system("clear");
		
		fclose(cpuinfo);
	}
	free(st);
	free(str);
	
   return 0;
}
