#include "binaryparser.h"

Block_t load_binary(FILE *fp) {

    Block_t block;

    if (!fread(&block.origin, sizeof(int32_t), 1, fp)) //
    {
        fprintf(stderr, "The origin block was not successfully read.");
    }

    if (!fread(&block.size, sizeof(int32_t), 1, fp)) //
    {
        fprintf(stderr, "The constant block was not successfully read.");
    }
    block.size = (int32_t) swap_uint32((uint32_t) block.size);

    block.data = (uint8_t*) malloc(block.size * sizeof(uint8_t));
    if (fread(block.data, sizeof(uint8_t), block.size, fp) != block.size) //
    {
        fprintf(stderr, "The data block was not successfully read.");
    }

    return block;
}

bool magic_bytes(FILE *fp)
{
    if (!fread(&magic_byte, sizeof(uint32_t), 1, fp))
    {
        fprintf(stderr, "The magic byte was not successfully read.");
    }
    magic_byte = swap_uint32(magic_byte);
    if (magic_byte != MAGIC_NUMBER)
    {
        fprintf(stderr, "The magic byte is not equivalent of the magic number.");
        return 0;
    }
    return 1;
}

void clear_binaryparser()
{
    free(constant_pool.data);
    free(text.data);
}
