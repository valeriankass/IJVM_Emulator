#include "util.h"
#include "binaryparser.h"

uint32_t swap_uint32(uint32_t num)
{
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

void increase_p_counter_by(int n)
{
    p_counter += n;
}

bool stack_is_full()
{
    if (stack.top >= stack.size) { return 1; }
    else return 0;
}

bool stack_is_empty()
{
    if (stack.top == -1) { return 1; }
    else return 0;
}

unsigned short byte_to_unsigned_short(uint8_t *data)
{
    return (data[0] << 8) | data[1];
}

short byte_to_signed_short(uint8_t *data)
{
    return ((data[2] << 8) & 0xff00) | (data[3] & 0xff);
}

short get_offset()
{
    if (p_counter < text.size) return byte_to_signed_short(&text.data[p_counter + 1]);
    else
    {
        fprintf(stderr, "The counter is larger or equal to the text block size.");
        return 0;
    }
}
