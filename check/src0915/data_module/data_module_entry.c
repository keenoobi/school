
#include "../data_libs/data_io.h"
#include "data_process.h"




void main()
{
    double *data;
    int n;
    
    scanf("%d", &n);
    data = malloc(sizeof(double) * n);
    //Don`t forget to allocate memory !

        input(data, &n);
        // output(data, n);

    if (normalization(data, n))
        output(data, n);
    else{
        printf("ERROR");
    }
    free(data);  
}
