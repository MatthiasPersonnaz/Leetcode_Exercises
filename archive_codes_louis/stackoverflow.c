#include <stdio.h>

int n = 0;

void main() {
    printf("%d\n", n++);
    main();
}
