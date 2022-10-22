#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int64_t ipow(int64_t base, uint8_t exp) {
    int64_t result = 1;

    /*
    if (exp >= 63) {
        if (base == 1) {
            return 1;
        }
        if (base == -1) {
            return 1 - 2 * (exp & 1); // (-1)^sgn(exp)
        }
        return 0; // guaranteed overflow for other bases
    }
    */

    while (1) {
        if (exp & 1) {  // odd exponent
            result *= base;
        }
        exp >>= 1; // right shift (integer divide exp by 2)
        if (!exp) { // exp = 0
            break;
        }
        base *= base;
    }

    return result;
}

int main(int argc, char **argv) {
    char *endptr;
    //int64_t base = strtoul(argv[1], &endptr, 10);
    //uint8_t exp = atoi(argv[2]);

    int64_t base = 10;
    uint8_t exp = 18;

    //printf("%ld\n", base);
    //printf("%d\n", exp);

    for (int i=0; i < 5000000; i++){
        ipow(base, exp);
    }
    printf("%ld\n", ipow(base, exp));

    return 0;
}
