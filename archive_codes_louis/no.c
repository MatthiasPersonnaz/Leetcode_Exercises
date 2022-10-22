#include <stdio.h>

int main (int argc, char* argv[]) {
    int n = 42;
    int* ptr = &n;
    
    int i = 1;
    
    while (1) {
        *(ptr+10*i) = 0;
        printf("%d\n", i);
        i++;
    }

    return 0;    
}
 
