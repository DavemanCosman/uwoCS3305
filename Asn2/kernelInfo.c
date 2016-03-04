#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cat /proc/cpuinfo | grep processor");
    system("cat /proc/version");
    return 0;
}
