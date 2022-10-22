#include <stdio.h>
#include <stdlib.h>

#define big unsigned long long int

big hyper(big a, big n, big b);
big power(big x, big y);

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("usage: ack m n\n");
    }
    
    big m = atoi(argv[1]);
    big n = atoi(argv[2]);
    
    big res = hyper(2, m, n+3) - 3;
    
    printf("ack(%llu, %llu) = %llu\n", m, n, res);
    
    return 0;
}

big hyper (big a, big n, big b) {
    if (n == 0) { // Succession
        return b + 1;
    } else if (n == 1) { // Addition
        return a + b;
    } else if (n == 2) { // Multiplication
        return a * b;
    } else if (n >= 3 && b == 0) {  // Base case, ends recursion
        return 1;
    } else if (n == 3) { // Exponentiation
        return power(a, b);
    } else {
        return hyper(a, n - 1, hyper(a, n, b - 1));
    }
}

big power(big x, big y) {
    big res = 1;
  
    while (y > 0)
    {
        if (y & 1)
            res = res*x;
        y = y>>1;
        x = x*x;
    }
    return res;
}
