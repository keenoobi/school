#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 100
#define HEIGHT 25
#define WIDTH 80
#define X_START 0.0
#define X_END 4 * M_PI
#define Y_START -1.0
#define Y_END 1.0
#define X_SEGMENT (X_END - X_START) / (WIDTH - 1)
#define Y_SEGMENT (Y_END - Y_START) / (HEIGHT - 1)

int is_operator(char c);
int precedence(char op);
int is_alphanumeric(char c);
int is_numeric(char c);
int check_infix(char* infix);
char* infixToPostfix(char* infix);
char* replace_word(const char* s, const char* oldW, const char* newW);
double evaluate_postfix(char* exp, int length, double x_value);

void display_field(char* postfix, int postfix_length, double (*eval)(char*, int, double));

int main() {
    char str[MAX_EXPR_SIZE];

    const char* functions[6] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
    const char* replace_functions[6] = {"S", "C", "T", "N", "Q", "L"};

    printf("Enter infix expression: \n");
    fgets(str, MAX_EXPR_SIZE, stdin);

    str[strcspn(str, "\n")] = '\0';

    char* str2 = str;

    for (int i = 0; i < 6; i++) {
        char* infix = replace_word(str2, functions[i], replace_functions[i]);
        str2 = infix;
        free(infix);
    }

    if (!check_infix(str2)) {
        char* postfix = infixToPostfix(str2);

        display_field(postfix, strlen(postfix), evaluate_postfix);
        free(postfix);
    }
    return 0;
}

// Function to check if the given character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '#' || c == 'S' || c == 'C' || c == 'T' ||
            c == 'N' || c == 'Q' || c == 'L');
}

// Function to check precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case 'S':
        case 'C':
        case 'T':
        case 'N':
        case 'Q':
        case 'L':
            return 3;
        case '#':
            return 4;
    }
    return -1;
}

int is_alphanumeric(char c) {
    int flg = 0;
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        flg = 1;
    }
    return flg;
}

int is_numeric(char c) {
    int flg = 0;
    if (c >= '0' && c <= '9') {
        flg = 1;
    }
    return flg;
}

char* infixToPostfix(char* infix) {
    int j = 0;
    char parenthesis_digit = '.';
    int len = strlen(infix);
    char* postfix = (char*)malloc(sizeof(char) * (2 * len + 2));
    char stack[MAX_EXPR_SIZE] = {0};
    int top = -1;

    for (int i = 0; i < len; i++) {
        if (infix[i] == ' ' || infix[i] == '\t') continue;

        if ((infix[i] == '-' && i == 0) ||
            (infix[i] == '-' && stack[top] == '(' && parenthesis_digit == '.')) {
            infix[i] = '#';  // unary minus
        }

        if (is_alphanumeric(infix[i]) && !is_alphanumeric(infix[i + 1])) {
            postfix[j++] = infix[i];
            if (stack[top] == '(') {
                parenthesis_digit = infix[i];
            }
            postfix[j++] = 32;
        } else if (is_alphanumeric(infix[i])) {
            postfix[j++] = infix[i];
            if (stack[top] == '(') {
                parenthesis_digit = infix[i];
            }
        }

        else if (infix[i] == '(') {
            stack[++top] = infix[i];
        }

        else if (infix[i] == ')') {
            parenthesis_digit = '.';
            while (top > -1 && stack[top] != '(') postfix[j++] = stack[top--];
            if (top > -1 && stack[top] != '(')
                return "Invalid Expression";
            else
                top--;
        }

        else if (is_operator(infix[i])) {
            while (top > -1 && precedence(stack[top]) >= precedence(infix[i])) postfix[j++] = stack[top--];
            stack[++top] = infix[i];
        }
    }

    while (top > -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';

    return postfix;
}

// Function to replase math function names with single characters
char* replace_word(const char* s, const char* oldW, const char* newW) {
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            i += oldWlen - 1;
        }
    }

    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

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

double evaluate_postfix(char* exp, int length, double x_value) {
    double stack[100] = {0};
    int top = 0;
    double a, b, result;
    double num = 0.0;
    char ch[2];

    for (int i = 0; i < length; i++) {
        if (is_numeric(exp[i])) {
            ch[0] = exp[i];
            ch[1] = '\0';
            num = num * 10 + strtod(ch, NULL);
        } else if (exp[i] == 'x') {
            num = num * 10 + x_value;
        } else if (exp[i] == 32) {
            stack[top] = num;
            top++;
            num = 0.0;
        }
        if (exp[i] == '#' || exp[i] == 'S' || exp[i] == 'C' || exp[i] == 'T' || exp[i] == 'N' ||
            exp[i] == 'Q' || exp[i] == 'L') {
            a = stack[--top];
            if (exp[i] == '#') {
                result = -1 * a;
            } else if (exp[i] == 'S') {
                result = sin(a);
            } else if (exp[i] == 'C') {
                result = cos(a);
            } else if (exp[i] == 'T') {
                result = tan(a);
            } else if (exp[i] == 'N') {
                result = tan(M_PI / 2 - a);
            } else if (exp[i] == 'Q') {
                result = sqrt(a);
            } else if (exp[i] == 'L') {
                result = log(a);
            }
            stack[top++] = result;
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            b = stack[--top];
            a = stack[--top];
            if (exp[i] == '+') {
                result = a + b;
            } else if (exp[i] == '-') {
                result = a - b;
            } else if (exp[i] == '*') {
                result = a * b;
            } else if (exp[i] == '/') {
                if (b == 0.0) {
                    b += 0.01;
                }
                result = a / b;
            }
            stack[top++] = result;
        }
    }
    return stack[--top];
}

void display_field(char* postfix, int postfix_length, double (*eval)(char*, int, double)) {
    char matrix[80][25];
    int cnt = 0;

    for (double x = X_START; x <= X_END + 0.05; x += X_SEGMENT) {
        double y = eval(postfix, postfix_length, x);
        double distance_y = y - Y_START;
        int yrange = (int)((distance_y + 0.01) / (Y_END - Y_START) * (HEIGHT - 1));

        for (int i = 0; i <= HEIGHT; i++) {
            if (i == yrange) {
                matrix[cnt][i] = '*';
            } else {
                matrix[cnt][i] = '.';
            }
        }
        cnt++;
    }
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            printf("%2c", matrix[i][25 - j - 1]);
        }
        if (j != HEIGHT - 1) {
            printf("\n");
        }
    }
}

int check_infix(char* infix) {
    int flg = 0;
    int length = strlen(infix);
    if (length > MAX_EXPR_SIZE) {
        printf("Invalid expression: input size is too long\n");
        flg = 1;
    } else {
        int cnt = 0;
        int i = 0;
        while (i < length && !flg) {
            if (cnt < 0) {
                printf("Invalid expression: different count of ( and )\n");
                flg = 1;
            }
            if (!is_operator(infix[i]) && !is_numeric(infix[i]) && infix[i] != 'x' && infix[i] != '(' &&
                infix[i] != ')' && infix[i] != ' ') {
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
            printf("Invalid expression: different count of ( and )");
            flg = 1;
        }
    }
    return flg;
}