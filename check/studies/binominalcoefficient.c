#include <stdio.h>

// Функция для вычисления факториала числа
int factorial(int n) {
if (n == 0)
return 1;
int factorial = 1;
for (int i = 1; i <= n; i++)
factorial = factorial * i;
return factorial;
}

// Функция для вычисления биномиального коэффициента C(n, k)
int binomialCoefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n;
    scanf("%d", &n); // Вводим значение n с помощью стандартного потока ввода
    for (int k = 0; k <= n; k++) {
        printf("%d", binomialCoefficient(n, k)); // Выводим биномиальный коэффициент
    }
    return 0;
}
