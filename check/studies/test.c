#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1)
        printf("n/a");
    else {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    }

    return 0;
}
int max(int *a, int n) {
    int maxsum = *a;
    for (int *p = a + 1; p - a < n; p++) {
        if (maxsum < *p) maxsum = *p;
    }
    return (maxsum);
}
int min(int *a, int n) {
    int minmin = *a;
    for (int *p = a + 1; p - a < n; p++) {
        if (minmin > *p) minmin = *p;
    }
    return (minmin);
}
double mean(int *a, int n) {
    double sum = *a;
    for (int *p = a + 1; p - a < n; p++) {
        sum = sum + *p;
    }
    sum = sum / n;
    return (sum);
}

double variance(int *a, int n) {
    double dis = 0;
    double mean1 = mean(a, n);
    for (int *p = a; p - a < n; p++) {
        dis += (*p - mean1) * (*p - mean1);
    }
    dis = dis / n;
    return (dis);
}
int input(int *a, int *n) {
    if (scanf("%d", n) == 1 && getchar() == '\n' && *n > 0 && *n <= NMAX) {
        for (int *p = a; p - a < *n; p++) {
            scanf("%d", p);
        }

    } else {
        return 1;
    }
    if (getchar() != '\n') return 1;

    return 0;
}
void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) printf("%d ", *p);
    printf("\n");
}
void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    int max = max_v;
    int min = min_v;
    double mean = mean_v;
    double variance = variance_v;
    printf("%d %d %.6lf %.6lf", max, min, mean, variance);
}
