#ifndef CONSTANT_DECLARATIONS_H
#define CONSTANT_DECLARATIONS_H

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

#endif