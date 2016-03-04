#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cat /proc/cpuinfo | grep processor");
    system("cat /proc/cpuinfo | grep vendor_id");
    system("cat /proc/version");
    return 0;
}
