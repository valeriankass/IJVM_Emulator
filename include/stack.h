#ifndef STACK_H
#define STACK_H

#include "ijvm.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int32_t top;
    size_t size;
    int32_t *array;

}Stack_t;

Stack_t stack;

Stack_t create_stuck();
void push(int32_t word);
int32_t pop();
void clear_stack();

#endif
