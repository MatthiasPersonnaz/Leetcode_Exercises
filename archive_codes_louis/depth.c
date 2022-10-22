#include <stdio.h>

void foo(long t[]);

int count = 0;
long t[] = {42, 1789, 32768, -101010, 17};

int main() {
    foo(t);
    return 0;
}

void foo(long t[]) {
    printf("%d\n", count++);
    foo(t);
}
