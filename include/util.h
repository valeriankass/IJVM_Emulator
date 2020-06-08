#ifndef UTIL_H
#define UTIL_H

/* debug print */
#ifdef DEBUG

#define dprintf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define dprintf(...)
#endif
uint32_t swap_uint32(uint32_t num);
bool stack_is_full();
bool stack_is_empty();
#endif
