#include "infix_to_postfix.h"

// Перевод строки из инфиксной записи в постфиксную
char* infix_to_postfix(char* infix) {
    int j = 0; //счетчик
    char parenthesis_digit = '.'; // для унарного минуса вставлять
    int len = strlen(infix);
    char* postfix = (char*)malloc(sizeof(char) * (2 * len + 2)); //чтобы с пробелом помещалось
    char stack[MAX_EXPR_SIZE] = {0};
    int top = -1;

    for (int i = 0; i < len; i++) {
        if (infix[i] == ' ' || infix[i] == '\t') continue; 

        if ((infix[i] == '-' && i == 0) ||
            (infix[i] == '-' && stack[top] == '(' && parenthesis_digit == '.')) { // проверка унарного минуса
            infix[i] = '#';  // Символ унарного минуса, для подчинения логике
        }
        if (is_alphanumeric(infix[i]) && !is_alphanumeric(infix[i + 1])) {//цифра+буква кидаем в постфикс + пробел, чтобы отличать числа друг от друга
            postfix[j++] = infix[i];
            if (stack[top] == '(') { //если скобка открыта то кидается в стек
                parenthesis_digit = infix[i]; //для унарного
            }
            postfix[j++] = 32;
        } else if (is_alphanumeric(infix[i])) {
            postfix[j++] = infix[i];
            if (stack[top] == '(') {
                parenthesis_digit = infix[i];
            }
        } else if (infix[i] == '(') { //если открытая скобка то на стек кидаем 
            stack[++top] = infix[i];
        } else if (infix[i] == ')') { //если закрытая скобка то перекидываем все что в стеке имеется
            parenthesis_digit = '.';
            while (top > -1 && stack[top] != '(') postfix[j++] = stack[top--];
            top--;
        } else if (is_operator(infix[i])) { // проверяем на значимость оператора
            while (top > -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }
    while (top > -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0'; //чтобы было строкой конец массива
    return postfix;
}

// Функция замены подстроки в строке
char* replace_word(const char* s, const char* oldW, const char* newW) { //заменить на буквы
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) { //возвращаем
            cnt++; //кол-во вхождений
            i += oldWlen - 1;
        }
    }
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); //память под новую строку
    i = 0;
    while (*s) {
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        } else {
            result[i++] = *s++;
        }
    }
    result[i] = '\0';
    return result;
}

// Функция проверки валидности инфиксной записи
int check_infix(char* infix) {
    int flg = 0;
    int length = strlen(infix);
    if (length > MAX_EXPR_SIZE) {
        printf("Invalid expression: input size is too long\n");
        flg = 1;
    } else {
        int cnt = 0; //подсчет скобочек
        int i = 0;
        while (i < length && !flg) {
            if (cnt < 0) {
                printf("Invalid expression: different count of ( and )\n");
                flg = 1;
            }
            if (!is_operator(infix[i]) && !is_numeric(infix[i]) && infix[i] != 'x' && infix[i] != '(' &&
                infix[i] != ')' && infix[i] != ' ') { //проверка на символы 
                printf("Invalid expession: prohibited symbols\n");
                flg = 1;
            }
            if (infix[i] == '(') {
                if (infix[i + 1] == ')') {
                    printf("Invalid expression: empty parentheses\n");
                    flg = 1;
                }
                cnt++;
            } else if (infix[i] == ')') {
                cnt--;
            }
            i++;
        }
        if (cnt > 0) {
            printf("Invalid expression: different count of ( and )\n");
            flg = 1;
        }
    }
    return flg;
}