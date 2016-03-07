#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

#define KNUM 100000

int main(void){

  int i,j, is_prime;
  int s;
  FILE* fp;

  fp = fopen("scanfiles", "w");
  i = 1;

  while (i < KNUM) {
        system ("od scanfiles > t");
        i++;
  }
}
