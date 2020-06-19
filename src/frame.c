#include "frame.h"

Frame_t *init_frame(int variable, int currentpc, int stackptr)
{
    Frame_t *frame;
    frame = (Frame_t*)malloc(sizeof(Frame_t));
    frame->variable = malloc(sizeof(int32_t));

    if(frame == NULL) fprintf(stderr, "Frame stack is empty.");
    if(frame->variable == NULL) fprintf(stderr, "The local variable in frame is empty.");

    frame->next = NULL;
    frame->currentpc = currentpc;
    frame->stackptr = stackptr;

    return frame;
}

Frame_t *get_current_frame()
{
    Frame_t *frame = current_frame;

    if (frame->next != NULL) frame = frame->next;

    return frame;
}
Frame_t *previous_frame()
{
    Frame_t *frame = current_frame;

  /**
    * we cannot get frame before the last
    * if the current frame is the last frame
    **/
    if(frame->next == NULL) {
	    fprintf(stderr, "%s", "ERROR: f->next == NULL\n");
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

