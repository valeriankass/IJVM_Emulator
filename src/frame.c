#include "frame.h"

Frame_t *init_frame(int current_top, int current_size, int current_p_counter)
{
    Frame_t *frame;
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

Frame_t *get_current_frame()
{
    Frame_t *frame = current_frame;

    if (frame->next != NULL) {frame = frame->next;}

    return frame;
}

int32_t get_local_variable(int i)
{
    return get_current_frame()->variable[i];
}
Frame_t *previous_frame()
{
    Frame_t *f = current_frame;

  /**
    * we cannot get frame before the last
    * if the current frame is the last frame
    */
    if(f->next == NULL) {
	    fprintf(stderr, "%s", "ERROR: f->next == NULL\n");
	    destroy_ijvm();
	    exit(1);
	}
    while ((f->next)->next != NULL) f = f->next;
    return f;
}

void clear_frame()
{
    Frame_t *tmp_frame;
    Frame_t *frame = current_frame;

    while (frame != NULL)
    {
        tmp_frame = frame;
        frame = frame->next;
        if (tmp_frame->variable != NULL) free(tmp_frame->variable);
        if (tmp_frame != NULL) free(tmp_frame);
    }
}

