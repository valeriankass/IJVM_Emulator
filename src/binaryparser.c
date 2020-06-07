#include "binaryparser.h"


uint32_t swap_uint32(uint32_t num)
{
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

Block_t load_binary(FILE *fp) {

    Block_t block;
    size_t origin;
    size_t size;

    if (fread(&origin, sizeof(int32_t), 1, fp) != 1) //
    {
        fprintf(stderr, "The origin block was not successfully read.");
    }
    origin = (size_t)swap_uint32((uint32_t)origin);
    block.origin = (word_t)origin;

    if (fread(&block.size, sizeof(int32_t), 1, fp) != 1) //
    {
        fprintf(stderr, "The constant block was not successfully read.");
    }
    size = (size_t)swap_uint32((uint32_t)size);
    block.size = (word_t)size;
    //block.size = (int32_t) swap_uint32((uint32_t) block.size);

    block.data = (byte_t*)malloc(size * sizeof(byte_t));
    if (fread(block.data, sizeof(uint8_t), 1, fp) != 1) //
    {
        fprintf(stderr, "The data block was not successfully read.");
    }
    return block;
}
