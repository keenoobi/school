#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include "graph.h"
int check_infix(char* infix);
char* infix_to_postfix(char* infix);
char* replace_word(const char* s, const char* oldW, const char* newW);

#endif