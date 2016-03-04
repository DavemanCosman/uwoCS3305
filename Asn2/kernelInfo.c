#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

main() {

   FILE *fp;
   char buff[255];

   fp = fopen("/proc/cpuinfo", "rb");
   fscanf(fp, "%s", buff);
   printf("1 : %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("2: %s\n", buff );
   
   fgets(buff, 255, (FILE*)fp);
   printf("3: %s\n", buff );
   fclose(fp);
}
