#ifndef FRAME_H
#define FRAME_H

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

//Frame_t *frame;
Frame_t *current_frame;
Frame_t *init_frame(int current_top, int current_size, int current_p_counter);
Frame_t *get_current_frame();

#endif
