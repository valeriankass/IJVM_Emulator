#ifndef UTIL_H
#define UTIL_H
#include "binaryparser.h"
#include "stack.h"
#include "machine.h"
#include "instructions.h"
#include "ijvm.h"
/* debug print */
#ifdef DEBUG

#define dprintf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define dprintf(...)
#endif
uint32_t swap_uint32(uint32_t num);
void increase_p_counter_by(int n);
bool stack_is_full();
bool stack_is_empty();
unsigned short byte_to_unsigned_short(uint8_t *data);
short byte_to_signed_short(uint8_t *data);
short get_signed_offset_byte_size();
unsigned short get_unsigned_offset_byte_size();
bool instruction_is_valid();
int32_t bytes_to_word(uint8_t *bytes);

#endif
