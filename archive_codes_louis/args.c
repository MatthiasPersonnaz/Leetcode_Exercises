#include <stdio.h>

int main (int argc, char* argv[]) {
    for (short i=0; argv[i] != 0; i++) {
        printf("argv[%d](%p): %s\n", i, argv[i], argv[i]);
    }
    return 0;    
}
