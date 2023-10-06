#ifndef EVALUATION_H
#define EVALUATION_H

#include "graph.h"
double evaluate_postfix(char* exp, int length, double x_value);
double unary_operation(char ch, double a);
double binary_operation(char ch, double a, double b);

#endif