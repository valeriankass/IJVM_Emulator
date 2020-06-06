#include "binaryparser.h"

Block_t block;

Block_t load_binary(FILE *fp) {

    if (!(fread(&block.origin, sizeof(int32_t), 1, fp))) //
    {
        fprintf(stderr, "The origin block was not successfully read.");
    }
    if (!(fread(&block.size, sizeof(int32_t), 1, fp))) //
    {
        fprintf(stderr, "The constant block was not successfully read.");
    }
    if (!(fread(&block.data, sizeof(uint8_t), 1, fp))) //
    {
        fprintf(stderr, "The text block was not successfully read.");
    }
    //add return of the block
}



