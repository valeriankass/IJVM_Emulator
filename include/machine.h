#ifndef MACHINE_H
#define MACHINE_H

#define BYTE 1
#define SHORT 2
#define WORD 4

#include "ijvm.h"
#include "util.h"
#include <stdint.h>
#include <stdlib.h>

int p_counter;
byte_t instruction;
FILE *file_out;
FILE *file_in;
FILE *get_input();

#endif
