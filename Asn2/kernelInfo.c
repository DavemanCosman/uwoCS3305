#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {

   FILE *fp;
   char buff[255];
   const char *vendor_id = "vendor_id";
   const char *model = "model";

   fp = fopen("/proc/cpuinfo", "rb");
   while (!feof(fp)){
      fscanf(fp, "%s", buff);
      if (strcmp(buff, vendor_id) == 0) {
         printf("%s", buff );
         fgets(buff, 255, (FILE*)fp);
         printf("%s\n", buff );
      }
      if (strcmp(buff, model) == 0) {
         printf("%s", buff );
         fgets(buff, 255, (FILE*)fp);
         printf("%s\n", buff );
      }
   }
   fclose(fp);
   
   fp = fopen("/proc/version", "rb");
   fgets(buff,255,(FILE*)fp);
   printf("%s\n", buff );
   return (0);
}
