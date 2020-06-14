#include "instructions.h"
#include "frame.h"

void BIPUSH(int32_t int_1)
{
    push(int_1);
}
void DUP()
{
    push(tos());
}
void ERR(){}
/*void GOTO()
{
    increase_p_counter_by(get_offset() - 1); // offset - 1 byte
}*/
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

}
void ILOAD() //TODO
{
    unsigned short index = get_unsigned_offset_byte_size();
    push(frame->variable[index]);
    increase_p_counter_by(2);
}
void INVOKEVIRTUAL(){}
void IOR()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 | int_2);
}
void IRETURN(){}
void ISTORE() //TODO
{

}
void ISUB()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_2 - int_1);
}
void LDC_W() //TODO
{
    unsigned short index = get_unsigned_offset_byte_size();
    push(get_constant(index));
    increase_p_counter_by(2);
    //1. Read the argument of the instruction (hereafter called the index). This index is represented using an unsigned short.
    //2. Load the word at offset index from the constant pool. Note: addressing in the constant pool is always done on a word-granularity level.
    //3. Push the loaded word to the stack.
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
void WIDE() //TODO: READ INSTRUCTIONS FOR WIDE ON ASSIGNMENT 2
{

}
