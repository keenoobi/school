#include "constants.h"
#include "display.h"
#include "evaluation.h"
#include "infix_to_postfix.h"
#include "verifications.h"

int main() {
    char str[MAX_EXPR_SIZE];

    const char* functions[6] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
    const char* replace_functions[6] = {"S", "C", "T", "N", "Q", "L"};

    printf("Enter infix expression:\n");
    fgets(str, MAX_EXPR_SIZE, stdin);

    str[strcspn(str, "\n")] = '\0';//выкидываем пернос строки с конца 

    char* str2 = str; //инициализация указателя для работы с стр

    for (int i = 0; i < 6; i++) {
        char* infix = replace_word(str2, functions[i], replace_functions[i]);
        str2 = infix;
        free(infix);
    }

    if (!check_infix(str2)) {
        char* postfix = infix_to_postfix(str2);

        display_field(postfix, strlen(postfix), evaluate_postfix);
        free(postfix);
    }
    return 0;
}