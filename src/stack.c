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
          fprintf(stderr, "%s", "ERROR (push): stack.data == NULL\n");
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
