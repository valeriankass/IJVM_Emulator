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

Block_t constant_pool;
Block_t text;

FILE *fp;
long int file_size;

uint32_t swap_uint32(uint32_t num);
Block_t load_binary(FILE *fp);


#endif
