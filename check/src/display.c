#include "display.h"

void display_field(char* postfix, int postfix_length, double (*eval)(char*, int, double)) { // поле, постфикс + длина + подсчет с указателем на эту штуку
    char matrix[80][25];
    int cnt = 0; // для прохода по количеству строк в матрице
    int nan_flg = 0; // для отлова нан значений (т.е не сигнальных чисел)

    for (double x = X_START; (x <= X_END + 0.05) && (!nan_flg); x += X_SEGMENT) {
        double y = eval(postfix, postfix_length, x); // считаем выражение
        if (isnan(y) == 1) {
            nan_flg = 1;
        }
        double distance_y = y - Y_START; // считает часть по точкам
        int yrange = (int)((distance_y + 0.01) / (Y_END - Y_START) * (HEIGHT - 1)); //у вычисляет общее рассотяние между  уэнд и устарт и +0,01 для избежания деления на ноль тем самым преобразуя в целое число

        for (int i = 0; i <= HEIGHT; i++) { // заполняем матрицу
            if (i == yrange) {
                matrix[cnt][i] = '*';
            } else {
                matrix[cnt][i] = '.';
            }
        }
        cnt++;
    }
    if (!nan_flg) { //транспонируем матрицу + поворачиваем
        for (int j = 0; j < HEIGHT; j++) { //цикл длины высчитываем 
            for (int i = 0; i < WIDTH; i++) { //цикл ширины высчитываем
                printf("%2c", matrix[i][25 - j - 1]); // по два элемента чтобы растянулось
            }
            if (j != HEIGHT - 1) { //перенос на новую строку 
                printf("\n");
            }
        }
    } else {
        printf("Error: NaN expression");
    }
}