
#include "data_io.h"

void input(double *data, int *n){
        
    for (double *p = data; p - data < *n; p++) {
            scanf("%lf", p);
        }


}

void output(double *data, int n){
   printf("%.2lf", *data);
   for (double *p = data + 1; p - data < n; p++){
        printf(" %.2lf", *p);
   }
    
}