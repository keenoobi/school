#include<stdio.h>

#define width 80
#define height 25

char mas [height][width];


void init()
{
    for(int i=0; i<width; i++)
        mas[0][i] = '#';
}

void show()
{
    printf("%s", mas[0]);
}

int main(){
    
    init();
    show();
    return 0;
}
