def pow(base, exp):
    result = 1
    while (True):
        if exp % 2 == 1:
            result *= base
        exp //= 2
        if (exp == 0):
            break
        base *= base
    return result


def main():
    for i in range(5000000):
        pow(10, 18)

if __name__ == "__main__":
    main()
