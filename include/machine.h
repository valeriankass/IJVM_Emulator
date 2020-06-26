#ifndef MACHINE_H
#define MACHINE_H

#define BYTE 1
#define SHORT 2

#include "ijvm.h"
#include "util.h"
#include "binaryparser.h"
#include "instructions.h"
#include "stack.h"
#include "frame.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int p_counter;
byte_t instruction;
FILE *file_out;
FILE *file_in;
FILE *get_input();

#endif
