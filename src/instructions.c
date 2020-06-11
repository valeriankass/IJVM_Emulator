#include "instructions.h"

void BIPUSH(int32_t int_1)
{
    push(int_1);
}
void DUP(){}
void ERR(){}
void GOTO(){}
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
void IFEQ(){}
void IFLT(){}
void ICMPEQ(){}
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
