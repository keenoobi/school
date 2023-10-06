#include<stdio.h>

int main(void){
    
    int numbers[5] = {10,12/* ,13,54,43 */};
    // numbers[0] = 1;
    // numbers[1] = 2;
    // numbers[2] = 3;
    // numbers[3] = 4;
    for (int i = 0; i < 5; i++)
    printf("numbers[%d] = %d \n", i, numbers[i]);
    // printf("numbers[1] = %d \n", numbers[1]);

    return 0;
}