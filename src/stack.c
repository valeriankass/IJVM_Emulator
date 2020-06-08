#include "stack.h"

Stack_t create_stack(size_t size)
{
    stack.top = -1;
    stack.size = size;
    if (!(stack.array = (int32_t*)malloc(sizeof(int32_t) * stack.size)))
    {
        fprintf(stderr, "Error in memory allocation of stack array.");
    }

    return stack;
}

void push(int32_t word)
{
    if (stack_is_full())
    {
        fprintf(stderr, "Push is not possible: the stack is full.");
    }
    else stack.array[stack.top++] = word;
}
int32_t pop()
{
    int32_t popped_top = 0;

    if (stack_is_empty())
    {
        fprintf(stderr, "Pop is not possible: the stack is empty.");
    }
    else
    {
        popped_top = stack.top;
        stack.top -= 1;
    }
    return popped_top;
}
void clear_stack()
{
    free(stack.array);
    stack.top = -1;
    stack.size = 0;
    stack.array = NULL;
}
