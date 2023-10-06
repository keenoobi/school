#include <stdio.h>

int main() {
    int sequence[1000];
    int num, i = 0;

    // Чтение последовательности чисел
    while (scanf("%d", &num) == 1) {
        // Проверка на конец последовательности
        if (num == -1) {
            break;
        }
        // Проверка на валидность введенных данных
        if (num < 0) {
            printf("n/a");
            return 0;
        }
        sequence[i] = num;
        i++;
    }

    // Вывод элементов последовательности в обратном порядке через пробел

    for (int j = i - 1; j >= 0; j--) {
        printf("%d\n", sequence[j]);
    }

    return 0;
}