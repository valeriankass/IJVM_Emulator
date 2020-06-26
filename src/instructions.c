#include "instructions.h"

bool step(void) //perform one instruction and return true or false
{
    instruction = get_instruction();
    switch (instruction)
    {
        case OP_BIPUSH :
            BIPUSH((int8_t)text.data[p_counter + BYTE]);
            break;
        case OP_DUP :
            DUP();
            break;
        case OP_ERR :
            ERR();
            break;
        case OP_GOTO : //unconditional jump
            increase_p_counter_by(get_signed_offset_byte_size() - BYTE);
            break;
        case OP_HALT : //halt the simulator
            return false;
            break;
        case OP_IADD :
            IADD();
            break;
        case OP_IAND :
            IAND();
            break;
        case OP_IFEQ :
            IFEQ();
            break;
        case OP_IFLT :
            IFLT();
            break;
        case OP_ICMPEQ :
            ICMPEQ();
            break;
        case OP_IINC :
            IINC();
            break;
        case OP_ILOAD :
            ILOAD();
            break;
        case OP_INVOKEVIRTUAL :
            INVOKEVIRTUAL();
            break;
        case OP_IOR :
            IOR();
            break;
        case OP_IRETURN :
            IRETURN();
            break;
        case OP_ISTORE :
            ISTORE();
            break;
        case OP_ISUB :
            ISUB();
            break;
        case OP_LDC_W :
            LDC_W();
            break;
        case OP_NOP :
            NOP();
            break;
        case OP_IN :
            IN();
            break;
        case OP_OUT :
            OUT();
            break;
        case OP_POP :
            POP();
            break;
        case OP_SWAP :
            SWAP();
            break;
        case OP_WIDE :
            increase_p_counter_by(BYTE);
            WIDE();
            break;
        default:
            return 0;
            break;
    }
    increase_p_counter_by(BYTE);
    return 1;
}
void BIPUSH(int32_t int_1) //Push a byte onto stack
{
    push(int_1);
    increase_p_counter_by(BYTE);
}
void DUP() //Copy top word on stack and push onto stack
{
    push(tos());
}
void ERR() //Print an error message and halt the simulator
{
    fprintf(stderr, "Error!");
    destroy_ijvm();
}
void IADD() //Pop two words from stack; push their sum
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 + int_2);
}
void IAND() //Pop two words from stack; push bit-wise AND
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 & int_2);
}
void IFEQ() //Pop word from stack and branch if it is zero
{
    if (pop() == 0) increase_p_counter_by(get_signed_offset_byte_size() - BYTE);
    else increase_p_counter_by(SHORT);
}
void IFLT() //Pop word from stack and branch if it is less than zero
{
    if (pop() < 0) increase_p_counter_by(get_signed_offset_byte_size() - BYTE);
    else increase_p_counter_by(SHORT);
}
void ICMPEQ() //Pop two words from stack and branch if they are equal
{
    int32_t word_1 = pop();
    int32_t word_2 = pop();

    if (word_1 == word_2) increase_p_counter_by(get_signed_offset_byte_size() - BYTE);
    else increase_p_counter_by(SHORT);
}
void IINC() //Add a constant value to a local variable. The first byte is the variable index.The second byte is the constant.
{
    Frame_t *frame = get_current_frame();
    int index = text.data[p_counter + BYTE];

    if (frame->variable_size < index + BYTE)
    {
        frame->variable_size = index + BYTE;
        frame->variable = realloc(frame->variable, (size_t)(frame->variable_size) * sizeof(word_t));
    }
    frame->variable[index] += (int8_t)text.data[p_counter + SHORT];
    increase_p_counter_by(SHORT);
}
void ILOAD() //Push local variable onto stack
{
    int index = text.data[p_counter + BYTE];
    push(get_local_variable(index));
    increase_p_counter_by(BYTE);
}
void INVOKEVIRTUAL() //Invoke a method, pops object reference and pops arguments from stack.
{
    Frame_t *frame;
    int current_p_counter;
    int argument_count;
    int local_variables;
    int constant_location;

    increase_p_counter_by(BYTE);
    current_p_counter = p_counter + BYTE;
    constant_location = byte_to_unsigned_short(&text.data[p_counter]);
    p_counter = get_constant(constant_location);
    argument_count = byte_to_unsigned_short(&text.data[p_counter]);
    increase_p_counter_by(SHORT);
    local_variables = byte_to_unsigned_short(&text.data[p_counter]);

    frame = init_frame(argument_count + local_variables, current_p_counter, stack_size() - argument_count);
    for (int i = argument_count - BYTE; i > 0; i--) {
        frame->variable[i] = pop();
    }
    get_current_frame()->next = frame;
    p_counter++;
}
void IOR() //Pop two word stack; push bit-wise OR.
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 | int_2);
}
void IRETURN() //Return from method with a word value
{
    	Frame_t *frame = get_current_frame();
    	word_t result = tos();

    	p_counter = frame->currentp_counter;
    	if(stack.size < frame->top) {
            fprintf(stderr, "stack_size() < f->top");
            destroy_ijvm();
            exit(1);
        }
        while(stack_size() > frame->top) {
    		pop();
    	}
    	//removing current frame
        previous_frame()->next = NULL;
        if (frame->variable != NULL) free(frame->variable);
        if (frame != NULL) free(frame);
    	push(result);
}
void ISTORE() //Pop word from stack and store in local variable
{
    int index = text.data[p_counter + BYTE];
    Frame_t *frame = get_current_frame();
    if (frame->variable_size < index + BYTE)
    {
        frame->variable_size = (size_t) index + BYTE;
        frame->variable = realloc(frame->variable, (size_t)(frame->variable_size) * sizeof(word_t));
    }
    frame->variable[index] = pop();
    increase_p_counter_by(1);
}
void ISUB() //Pop two words from stack; subtract the top word from the second to top word, push the answer;
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_2 - int_1);
}
void LDC_W() //Push constant from constant pool onto stack
{
    unsigned short index = get_unsigned_offset_byte_size();
    push(get_constant(index));
    increase_p_counter_by(SHORT);
}
void NOP(){} //Do nothing
void IN() //Reads a character from the input and pushes it onto the stack. If no character is available, 0 is pushed
{
    int input = fgetc(file_in);

    if (input != EOF) push(input);
    else push(0);
}
void OUT() //Pop word off stack and print it to standard out
{
    char output = (char) pop();
    fputc(output, file_out);
}
void POP() //Delete word from top of stack
{
    pop();
}
void SWAP() //Swap the two top words on the stack
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1);
    push(int_2);
}
bool WIDE() //Prefix instruction; next instruction has a 16-bit index
{
    Frame_t *frame = get_current_frame();
    short signed_index = get_signed_offset_byte_size();
    unsigned short unsigned_index = get_unsigned_offset_byte_size();

    switch(text.data[p_counter])
    {
        case OP_BIPUSH:
            push(signed_index);
            increase_p_counter_by(SHORT);
        break;
        case OP_ILOAD:
            push(get_local_variable(unsigned_index));
            increase_p_counter_by(SHORT);
        break;
        case OP_ISTORE:

            if (frame->variable_size < unsigned_index + BYTE)
            {
                frame->variable_size = unsigned_index + BYTE;
                frame->variable = realloc(frame->variable, (size_t)(frame->variable_size) * sizeof(word_t));
            }
            frame->variable[unsigned_index] = pop();
            increase_p_counter_by(SHORT);
        break;
        default:
            return 0;
        break;
    }
    return 1;
}

