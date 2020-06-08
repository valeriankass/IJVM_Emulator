#include "binaryparser.h"
#include "stack.h"

uint32_t swap_uint32(uint32_t num)
{
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

bool stack_is_full()
{
    if (stack.top >= stack.size - 1) { return 1; }
    else return 0;
}

bool stack_is_empty()
{
    if (stack.top == -1) { return 1; }
    else return 0;
}
