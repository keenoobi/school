#include "verifications.h"

// Функция проверки символа на оператор
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '#' || c == 'S' || c == 'C' || c == 'T' ||
            c == 'N' || c == 'Q' || c == 'L');
}

// Функция проверки приоритета операторов
int precedence(char op) {
    int flg = -1;
    if (op == '+' || op == '-') {
        flg = 1;
    } else if (op == '*' || op == '/') {
        flg = 2;
    } else if (op == 'S' || op == 'C' || op == 'T' || op == 'N' || op == 'Q' || op == 'L') {
        flg = 3;
    } else if (op == '#') {
        flg = 4;
    }
    return flg;
}

// Проверка символа на цифру/букву
int is_alphanumeric(char c) {
    int flg = 0;
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        flg = 1;
    }
    return flg;
}

// Проверка символа на цифру
int is_numeric(char c) {
    int flg = 0;
    if (c >= '0' && c <= '9') {
        flg = 1;
    }
    return flg;
}