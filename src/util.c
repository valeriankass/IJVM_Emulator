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
    return (unsigned short) (data[0] << 8) | data[1];
}

short byte_to_signed_short(uint8_t *data)
{
    return (short) ((data[0] << 8) & 0xff00) | (data[1] & 0xff);
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
bool instruction_is_valid()
{
    if (instruction == OP_BIPUSH ||
    instruction == OP_DUP ||
    instruction == OP_ERR ||
    instruction == OP_GOTO ||
    instruction == OP_HALT ||
    instruction == OP_IADD ||
    instruction == OP_IAND ||
    instruction == OP_IFEQ ||
    instruction == OP_IFLT ||
    instruction == OP_ICMPEQ ||
    instruction == OP_IINC ||
    instruction == OP_ILOAD ||
    instruction == OP_INVOKEVIRTUAL ||
    instruction == OP_IOR ||
    instruction == OP_IRETURN ||
    instruction == OP_ISTORE ||
    instruction == OP_ISUB ||
    instruction == OP_LDC_W ||
    instruction == OP_NOP ||
    instruction == OP_IN ||
    instruction == OP_OUT ||
    instruction == OP_POP ||
    instruction == OP_SWAP ||
    instruction == OP_WIDE) return 1;
    else return 0;
}
