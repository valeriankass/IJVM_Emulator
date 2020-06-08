#include "instructions.h"

void BIPUSH(int32_t integer_1)
{
    push(integer_1);
}
void DUP(){}
void ERR(){}
void GOTO(){}
void HALT(){}
void IADD(){}
void IAND(){}
void IFEQ(){}
void IFLT(){}
void ICMPEQ(){}
void IINC(){}
void ILOAD(){}
void INVOKEVIRTUAL(){}
void IOR(){}
void IRETURN(){}
void ISTORE(){}
void ISUB(){}
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
void SWAP(){}
void WIDE(){}

