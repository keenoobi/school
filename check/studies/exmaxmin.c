#include <stdio.h>

int main() {
    int number, largest = 0;
    printf("Enter the sequence of numbers (-1 to end): ");
    
    while (1) {
        scanf("%d", &number);
        if (number == -1) {
            break;
        }
        if (number > largest) {
            largest = number;
        }
    }
    
    printf("The largest number is %d\n", largest);
    return 0;
}
