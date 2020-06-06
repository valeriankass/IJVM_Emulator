#ifndef BINARYPARSER_H
#define BINARYPARSER_H

#include "ijvm.h"
#include "util.h"
#include <stdint.h>

typedef struct Block {
    int32_t *origin;
    int32_t *size;
    uint8_t *data;
}Block_t;

Block_t constant_pool;
Block_t text;

FILE *fp;
long int file_size;

Block_t load_binary(FILE *fp);

#endif
