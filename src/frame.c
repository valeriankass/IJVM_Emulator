#include "frame.h"

Frame_t *init_frame(int variable_size, int current_p_counter, int stack_top)
{
    Frame_t *frame;
    frame = (Frame_t*)malloc(sizeof(Frame_t));
    frame->variable_size = variable_size;
    frame->variable = malloc((size_t)(variable_size) * sizeof(word_t));

    if(frame == NULL) fprintf(stderr, "Frame stack is empty.");
    if(frame->variable == NULL) fprintf(stderr, "The local variable in frame is empty.");

    frame->next = NULL;
    frame->currentp_counter = current_p_counter;
    frame->top = stack_top;

    return frame;
}

Frame_t *get_current_frame()
{
    Frame_t *frame = current_frame;

    while (frame->next != NULL) frame = frame->next;

    return frame;
}
Frame_t *previous_frame()
{
    Frame_t *frame = current_frame;

    if(frame->next == NULL) {
	    fprintf(stderr, "The next frame is empty.");
	    destroy_ijvm();
	    exit(1);
	}
    while ((frame->next)->next != NULL) {
        frame = frame->next;
    }
    return frame;
}


int32_t get_local_variable(int i)
{
    return get_current_frame()->variable[i];
}

void clear_frame()
{
    Frame_t *frame = current_frame;

    while (frame != NULL)
    {
        if (frame->variable != NULL) free(frame->variable);
        if (frame != NULL) free(frame);
        frame = frame->next;
    }
}

