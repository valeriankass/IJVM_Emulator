#ifndef STACK_H
#define STACK_H

#include "ijvm.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int top;
    int size;
    int32_t *array;
}Stack_t;

Stack_t stack;

void create_stack(int size);
void push(int32_t word);
int32_t pop(void);
void clear_stack(void);

#endif
