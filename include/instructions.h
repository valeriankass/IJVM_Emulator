#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "ijvm.h"
#include "util.h"
#include <stdint.h>
#include <unistd.h>

void BIPUSH();
void DUP();
void ERR();
void GOTO();
void HALT();
void IADD();
void IAND();
void IFEQ();
void IFLT();
void ICMPEQ();
void IINC();
void ILOAD();
void INVOKEVIRTUAL();
void IOR();
void IRETURN();
void ISTORE();
void ISUB();
void LDC_W();
void NOP();
void OUT();
void POP();
void SWAP();
void WIDE();

#endif
