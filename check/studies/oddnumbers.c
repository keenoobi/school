#include <stdio.h>

int main() {
    int number, digit, product = 1;

    // printf("Please enter a positive integer: ");
    if (scanf("%d", &number) != 1 || number <= 0) {
        printf("n/a");
        return 0;
    }

    while (number > 0) {
        digit = number % 10;
        if (digit % 2 != 0) {
            product *= digit;
        }
        number /= 10;
    }

    if (product == 1) {
        printf("0");
    } else {
        printf("%d", product);
    }

    return 0;
}
