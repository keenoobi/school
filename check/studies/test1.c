#include <stdio.h>
int main()
{
for (int x = 0; x < 25; x++)
 {
    for (int y = 0; y < 80; y++)
    {
        if( x == 0 || x == 24)
        {
            printf("#");
        }
        else
        {
            if (y == 0 || y == 79)
            {
                 printf("#");
            }
            if ( y == 39)
            {
                printf("|");
            }
           
            else
            {
                printf(" ");
            }
        }
    }
    
    printf("\n");
    
 }
}
