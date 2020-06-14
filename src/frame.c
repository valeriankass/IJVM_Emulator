#include <stdio.h>
#include "frame.h"

Frame_t *load_frame(int current_top, int current_size, int current_p_counter)
{
    frame = (Frame_t*)malloc(sizeof(Frame_t));
    frame->variable = malloc((size_t)(current_size) * sizeof(int32_t));

    if(frame == NULL) fprintf(stderr, "Frame stack is empty.");
    if(frame->variable == NULL) fprintf(stderr, "The local variable in frame is empty.");

    frame->p_counter = current_p_counter;
    frame->size = current_size;
    frame->top = current_top;
    frame->next = NULL;

    return frame;
}


