#include <stdlib.h>

int *newData(int *data, int *flag, int count) {
    int *tmp = (int *)malloc((sizeof(int) * count) + (10 * sizeof(int)));
    for (int i = 0; i < count; i++) {
        tmp[i] = data[i];
    }
    free(data);
    (*flag)++;  // Увеличиваем значение флага на 1
    return tmp;
}

int main() {
    int *data;
    int flag = 0;  // Изменяем начальное значение флага на 0
    data = (int *)malloc(10 * sizeof(int));

    int i = 0;
    int num = 0;
    while (num != -1) {
        scanf("%d", &num);
        if (num != -1) {
            data[i] = num;
            i++;
        }
        if (i % 10 == 0) {
            data = newData(data, &flag, i);
        }
    }
    for (int z = 0; z < i; z++) {
        printf("%d ", data[z]);  // Добавляем пробел после каждого числа для разделения вывода
    }
    printf("\n");  // Добавляем новую строку после вывода всех чисел
    free(data);
    return 0;
}