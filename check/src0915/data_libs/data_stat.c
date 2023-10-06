#include "data_stat.h"


double max(double *data, int n){
    double maxsum = *data;
    for (double *p = data + 1; p - data < n; p++) {
        if (maxsum < *p) maxsum = *p;
    }
    return (maxsum);

}
double min(double *data, int n){
    double minmin = *data;
    for (double *p = data + 1; p - data < n; p++) {
        if (minmin > *p) minmin = *p;
    }
    return (minmin);

}
double mean(double *data, int n){
    double sum = *data;
    for (double *p = data + 1; p - data < n; p++) {
        sum = sum + *p;
    }
    sum = sum / n;
    return (sum);

}
double variance(double *data, int n){
    double dis = 0;
    double mean1 = mean(data, n);
    for (double *p = data; p - data < n; p++) {
        dis += (*p - mean1) * (*p - mean1);
    }
    dis = dis / n;
    return (dis);

}
