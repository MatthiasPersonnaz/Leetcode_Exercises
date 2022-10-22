#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char BYTE;

int main(int argc, char* argv[]) {
    unsigned long long int size = 100000000; // 100 MB
    int i = 0;
    BYTE* ptr;
    printf("sizeof(BYTE): %lu\n", sizeof(BYTE));
    
    while (++i > 0) {
        getchar(); // wait for ENTER hit
        ptr = (BYTE*)malloc(size);
        memset(ptr, 0, size);
        printf("allocated %lld bytes", size);
    }
    
    return 0;
}

