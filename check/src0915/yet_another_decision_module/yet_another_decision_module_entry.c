
#include "../data_libs/data_io.h"
#include "decision.h"



void main()
{
    double *data;
    int n;
    
    scanf("%d", &n);
    data = malloc(sizeof(double) * n);

    input(data, &n);

    if (make_decision(data, n))
        printf("YES"); 
    else
        printf("NO");  

    free(data);  
}
