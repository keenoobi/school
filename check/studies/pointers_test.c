#include <stdio.h>

int main(){
    int d = 10;
    int *gpt = &d;

    //gpt = &d;

    printf("gpt = %p, *gpt = %d, d = %d\n", gpt, *gpt, d);

    *gpt = 100;

    printf("gpt = %p, *gpt = %d, d = %d\n", gpt, *gpt, d);

    return 0;
}