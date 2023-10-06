#include "evaluation.h"

// Функция подсчета значения, заданного в постфиксной форме
double evaluate_postfix(char* exp, int length, double x_value) {
    double stack[100] = {0};
    int top = 0; // верхний элемент стэка
    double a, b, result;
    double num = 0.0;
    char ch[2];

    for (int i = 0; i < length; i++) {
        if (is_numeric(exp[i])) {// проверка явл. ли числом
            ch[0] = exp[i];
            ch[1] = '\0';
            num = num * 10 + strtod(ch, NULL); //переводит в даб
        } else if (exp[i] == 'x') {
            num = num * 10 + x_value;
        } else if (exp[i] == 32) {
            stack[top] = num; // число в стек
            top++;
            num = 0.0; // для дальнейшего подсчитывания
        }
        if (exp[i] == '#' || exp[i] == 'S' || exp[i] == 'C' || exp[i] == 'T' || exp[i] == 'N' ||
            exp[i] == 'Q' || exp[i] == 'L') {
            a = stack[--top];

            result = unary_operation(exp[i], a);//одно число применяется к операции и закидывается в стек
            stack[top++] = result;
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            b = stack[--top];
            a = stack[--top];

            result = binary_operation(exp[i], a, b);
            stack[top++] = result;
        }
    }
    return stack[--top];// берем последний элемент
}

// Функция применения унарного оператора
double unary_operation(char ch, double a) {
    double result = 0.0;
    if (ch == '#') {
        result = -1 * a;
    } else if (ch == 'S') {
        result = sin(a);
    } else if (ch == 'C') {
        result = cos(a);
    } else if (ch == 'T') {
        result = tan(a);
    } else if (ch == 'N') {
        result = tan(M_PI / 2 - a);
    } else if (ch == 'Q') {
        result = sqrt(a);
    } else if (ch == 'L') {
        result = log(a);
    }
    return result;
}

// Функция применения бинарного оператора
double binary_operation(char ch, double a, double b) {
    double result = 0.0;
    if (ch == '+') {
        result = a + b;
    } else if (ch == '-') {
        result = a - b;
    } else if (ch == '*') {
        result = a * b;
    } else if (ch == '/') {
        if (b == 0.0) {
            b += 0.01;// чтобы не было не было бесконечно 
        }
        result = a / b;
    }
    return result;
}