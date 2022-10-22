/**
 * An implementation of the hyper operator that starts with succession
 * defined as 0. Shortcuts for operator values less than 4 have been added.
 * This implementation uses the following integers as operators:
 *
 * 0 - Succession (add 1 to b)
 * 1 - Addition (a + 1, b times)
 * 2 - Multiplication (a plus itself, b times)
 * 3 - Exponentiation (a times itself, b times)
 *
 * And so on.
 *
 * NOTE: This implementation is designed only to satisfy what is needed for
 * the Ackermann function and was not designed to handle things like negative
 * arguments and such. If you need a general purpose hyper function (method),
 * look else where.
 *
 * @param a The left operand. In "1 + 3", 1 is the left operand.
 * @param n The operator (+,*,^) to use. See above table for list of operators.
 * @param b The right operand. In "3 ^ 4", 4 is the right operand.
 * @return The result of applying the given operation on integers a and b.
 */
static hyper(BigInteger a, BigInteger n, BigInteger b) {
    if (n == 0) { // Succession
        return b + 1
    } else if (n == 1) { // Addition
        return a + b
    } else if (n == 2) { // Multiplication
        return a * b
    } else if (n >= 3 && b == 0) {  // Base case, ends recursion
        return 1
    } else if (n == 3) { // Exponentiation
        return a.pow(b)
    } else {
        return hyper(a, n - 1, hyper(a, n, b - 1))
    }
}

/**
 * An efficient enough Ackermann function to compute ack(4,2) in less than a
 * second.
 *
 * @param m (Integer) The first argument to the Ackermann function
 * @param n (Integer) The second argument to the Ackermann function
 * @return The result of ack(m, n)
 */
static ackermann(m, n) {
    return hyper(2, m, n+3) - 3;
}

/*
 * Compute ack(m, n) for all values of m and n between 0 and 4 inclusive.
 * Each run will be timed and printed out with how long the time took and
 * what the resulting Ackermann number is.
 *
 * NOTE: ack(4, 3) and ack(4, 4)
 * report incredibly low numbers. These numbers are incorrect. This happens
 * because of an integer overflow issue. BigInteger's pow method doesn't
 * accept another BigInteger as an exponent (it accepts an int). When the
 * BigInteger is transformed into an int, we lose our progress and end up
 * overflowing to a small number. This can be prevented by using a custom
 * exponentiation method (function).
 */

for (BigInteger m in 0..4) {
    for (BigInteger n in 0..4) {
        long start = System.currentTimeMillis()
        BigInteger result = ackermann(m, n)
        long end = System.currentTimeMillis()
        long duration = end - start
        println "Ackermann($m, $n):\t(${duration}ms)\t $result"
    }
} 
