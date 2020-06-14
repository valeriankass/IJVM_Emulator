#ifndef BINARYPARSER_H
#define BINARYPARSER_H

#include "ijvm.h"
#include "util.h"
#include "stack.h"
#include "machine.h"
#include "binaryparser.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Frame
{
    int top;
    int size;
    int32_t *variable;
    int p_counter;
    struct Frame *next;
}Frame_t;

Frame_t *frame;


#endif
