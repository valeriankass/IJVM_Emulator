#ifndef BINARYPARSER_H
#define BINARYPARSER_H

#include "ijvm.h"
#include "util.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Block {
    int32_t origin;
    int32_t size;
    uint8_t *data;
}Block_t;

uint32_t magic_byte;

Block_t constant_pool;
Block_t text;

Block_t load_binary(FILE *fp);
bool magic_bytes(FILE *fp);
void clear_binaryparser();


#endif
