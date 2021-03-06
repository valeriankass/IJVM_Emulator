#include "stack.h"

void create_stack(int size)
{
    stack.top = 0;
    stack.size = size;
    stack.array = malloc(sizeof(int32_t) * stack.size);
    if (stack.array == NULL)
    {
        fprintf(stderr, "Error in memory allocation of stack array.");
    }
}

void push(int32_t word)
{
    if (stack_is_full())
    {
        stack.size *= 2;
        stack.array = realloc(stack.array, (size_t)stack.size * sizeof(word_t));
        if(stack.array == NULL) {
          fprintf(stderr, "The stack array is empty.");
          exit(1);
        }
    }
    stack.array[stack.top++] = word;
}
int32_t pop()
{
    return stack.array[--stack.top];
}
void clear_stack()
{
    free(stack.array);
    stack.top = -1;
    stack.size = 0;
    stack.array = NULL;
}
word_t *get_stack(void)
{
    return stack.array;
}
int stack_size(void)
{
    return stack.top;
}
word_t tos() //returns a word on top of the stack of current frame
{
    if(stack.top > get_current_frame()->top) return stack.array[stack.top - 1];
    else
    {
        fprintf(stderr, "stack.top <= get_current_frame()->top");
        destroy_ijvm();
        return -1;
    }
}
