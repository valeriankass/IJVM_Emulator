#include "instructions.h"

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
    if (pop() == 0) increase_p_counter_by(get_offset() - 1);
    else increase_p_counter_by(2);
}
void IFLT()
{
    if (pop() < 0) increase_p_counter_by(get_offset() - 1);
    else increase_p_counter_by(2);
}
void ICMPEQ()
{
    int32_t word_1 = pop();
    int32_t word_2 = pop();

    if (word_1 == word_2) increase_p_counter_by(get_offset() - 1);
    else increase_p_counter_by(2);
}
void IINC(){}
void ILOAD(){}
void INVOKEVIRTUAL(){}
void IOR()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_1 | int_2);
}
void IRETURN(){}
void ISTORE(){}
void ISUB()
{
    int32_t int_1, int_2;

    int_1 = pop();
    int_2 = pop();
    push(int_2 - int_1);
}
void LDC_W(){}
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
void WIDE(){}
