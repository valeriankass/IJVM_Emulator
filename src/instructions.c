#include "instructions.h"
#include "frame.h"
#include "machine.h"

void BIPUSH(int32_t int_1)
{
    push(int_1);
}
void DUP()
{
    push(tos());
}
void ERR(){}
void IADD()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 + int_2);
}
void IAND()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 & int_2);
}
void IFEQ()
{
    if (pop() == 0) increase_p_counter_by(get_signed_offset_byte_size() - 1);
    else increase_p_counter_by(2);
}
void IFLT()
{
    if (pop() < 0) increase_p_counter_by(get_signed_offset_byte_size() - 1);
    else increase_p_counter_by(2);
}
void ICMPEQ()
{
    int32_t word_1 = pop();
    int32_t word_2 = pop();

    if (word_1 == word_2) increase_p_counter_by(get_signed_offset_byte_size() - 1);
    else increase_p_counter_by(2);
}
void IINC() //TODO
{
    Frame_t *frame = get_current_frame();
    int index = text.data[p_counter + 1];

    if (sizeof(frame) < index + 1)
    {
        int new_size = index + 1;
        frame->variable = realloc(frame->variable, (size_t)(new_size) * sizeof(word_t));
    }
    frame->variable[index] += (int8_t)text.data[p_counter + 2];
    increase_p_counter_by(2);
}
void ILOAD()
{
    int index = text.data[p_counter + 1];
    push(get_local_variable(index));
    increase_p_counter_by(1);
}
void INVOKEVIRTUAL()
{
    	Frame_t *frame;
    	int currentpc;
    	int argsCount;
    	int localVars;
    	int constantLoc;

    	increase_p_counter_by(1);
    	currentpc = p_counter + 1;
    	constantLoc = byte_to_unsigned_short(&text.data[p_counter]);
    	p_counter = get_constant(constantLoc);
    	argsCount = byte_to_unsigned_short(&text.data[p_counter]);
    	increase_p_counter_by(2);
    	localVars = byte_to_unsigned_short(&text.data[p_counter]);

    	frame = init_frame(argsCount + localVars, currentpc, stack_size() - argsCount);
    	for (int i = argsCount - 1; i > 0; i--) {
    		frame->variable[i] = pop();
    	}
    	get_current_frame()->next = frame;
    	p_counter++;
} //p.5 saving prev pc
void IOR()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 | int_2);
}
void IRETURN()
{
    	Frame_t *frame = current_frame;
    	word_t result = tos();

    	p_counter = frame->currentpc;
    	if(stack_size() < frame->stackptr) {
            fprintf(stderr, "%s", "ERROR: stack_size() < f->stack_pointer\n");
            destroy_ijvm();
            exit(1);
        }
        while(stack_size() > frame->stackptr) {
    		pop();
    	}
        previous_frame()->next = NULL;
        if (frame->variable != NULL) free(frame->variable);
        if (frame != NULL) free(frame);
    	BIPUSH(result);
}
void ISTORE()
{
    int index = text.data[p_counter + 1];
    Frame_t *frame = get_current_frame();
    if (sizeof(frame) < index + 1)
    {
        int new_size = index + 1;
        frame->variable = realloc(frame->variable, (size_t)(new_size) * sizeof(word_t));
    }
    frame->variable[index] = pop();
    increase_p_counter_by(1);
}
void ISUB()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_2 - int_1);
}
void LDC_W()
{
    unsigned short index = get_unsigned_offset_byte_size();
    push(get_constant(index));
    increase_p_counter_by(2);
}
void NOP(){}
void IN()
{
    int input = fgetc(file_in);

    if (input != EOF)
    {
        push(input);
    }
    else push(0);
}
void OUT()
{
    char output = (char) pop();
    fputc(output, file_out);
}
void POP()
{
    pop();
}
void SWAP(){
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1);
    push(int_2);
}
bool WIDE()
{
    Frame_t *frame = get_current_frame();
    short signed_index = get_signed_offset_byte_size();
    unsigned short unsigned_index = get_unsigned_offset_byte_size();

    increase_p_counter_by(1);
    switch(text.data[p_counter])
    {
        case OP_ILOAD:
            push(get_local_variable(unsigned_index));
            increase_p_counter_by(2);
        break;
        case OP_ISTORE:

            if (sizeof(frame) < unsigned_index + 1)
            {
                int new_size = unsigned_index + 1;
                frame->variable = realloc(frame->variable, (size_t)(new_size) * sizeof(word_t));
            }
            frame->variable[unsigned_index] = pop();
            increase_p_counter_by(2);
        break;
        case OP_IINC:

            if (sizeof(frame) < signed_index + 1)
            {
                int new_size = signed_index + 1;
                frame->variable = realloc(frame->variable, (size_t)(new_size) * sizeof(word_t));
            }
            frame->variable[signed_index] += byte_to_signed_short(&text.data[p_counter + 3]);
            increase_p_counter_by(4);
        break;
        default:
            return 0;
        break;
    }
    return 1;
}

