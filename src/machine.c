#include "machine.h"

int init_ijvm(char *binary_file)
{
    FILE *fp;
    p_counter = 0;
    set_input(stdin);
    set_output(stdout);

    if (!(fp = fopen(binary_file, "r"))) //opening file and checking if it was opened successfully
    {
        fprintf(stderr, "The file was not opened successfully.");
        return -1;
    }
    if (fp == NULL) //checking if file exists
    {
        fprintf(stderr, "The file does not exist.");
        return -1;
    }
    if (!magic_bytes(fp)) {
        fprintf(stderr, "No magic bytes.");
        return -1;
    }
    constant_pool = load_binary(fp);
    text = load_binary(fp);

    current_frame = init_frame(0,0,0);
    create_stack(16);

    fclose(fp);
    return 0;
}

void destroy_ijvm()
{
    clear_binaryparser();
    clear_stack();
    clear_frame();
}

void run()
{
    while (p_counter <= text.size) if (!step()) break;
}
bool finished()
{
    if (&text.data[stack.size - BYTE] == NULL || instruction == OP_HALT || instruction == OP_ERR || instruction_is_valid()) return 1;
    else return 0;
}

int text_size(void) //Returns the size of the currently loaded program text
{
    return text.size;
}

byte_t *get_text(void) //Returns the currently loaded program text as a byte array.
{
    return text.data;
}
word_t get_constant(int i) //work on it by transferring the byte_t to word_t
{
    long index = i * (int)sizeof(int32_t);

    if(i >= constant_pool.size) {
        fprintf(stderr, "The i is larger than the constant pool size.");
        destroy_ijvm();
    }
    return bytes_to_word(&constant_pool.data[index]);
}

int get_program_counter(void) //Returns the value of the program counter (as an offset from the first instruction).
{
    return p_counter;
}

byte_t get_instruction() //return The value of the current instruction represented as a byte_t
{
    return text.data[p_counter];
}

void set_input(FILE *fp)
{
    file_in = fp;
}

void set_output(FILE *fp)
{
    file_out = fp;
}
