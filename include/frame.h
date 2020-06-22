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
    int32_t *variable;
    struct Frame *next; //prev
    int currentp_counter;
    int top;
    size_t variable_size;
}Frame_t;

//Frame_t *frame;
Frame_t *current_frame;
Frame_t *init_frame();
Frame_t *get_current_frame();
void clear_frame();
Frame_t *previous_frame();

#endif
