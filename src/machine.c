#include "ijvm.h"
#include "util.h"
#include "binaryparser.h"
#include "instructions.h"
#include "stack.h"
#include "machine.h"
#include <stdio.h>
#include <unistd.h>


int init_ijvm(char *binary_file)
{
    FILE *fp;
    p_counter = 0;
    file_in = stdin;
    file_out = stdout;

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
    create_stack(10000);

    fclose(fp);
    return 0;
}

word_t tos(void) //returns a word on top of the stack of current frame
{
    return stack.array[stack.top - 1];
}
/**
 * Returns the stack of the current frame as an array of integers,
 * with entry[0] being the very bottom of the stack and
 * entry[stack_size() - 1] being the top.
 **/
word_t *get_stack(void)
{
    return stack.array;
}
int stack_size(void)
{
    return stack.size;
}
word_t get_local_variable(int i) //TODO
{
    return 0;
}
void destroy_ijvm()
{
    clear_binaryparser();
    clear_stack();
}

void run()
{
    while (p_counter <= text.size)
    {
        step();
    }
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
    return constant_pool.data[i];
}

int get_program_counter(void) //Returns the value of the program counter (as an offset from the first instruction).
{
    return p_counter;
}
bool step(void) //perform one instruction and return true or false
{
    byte_t instruction = get_instruction();
    if (p_counter <= text.size)
    {
        switch (instruction)
        {
            case OP_BIPUSH :
                BIPUSH();
                break;
            case OP_DUP :
                DUP();
                break;
            case OP_ERR :
                ERR();
                break;
            case OP_GOTO :
                GOTO();
                break;
            case OP_HALT :
                HALT();
                break;
            case OP_IADD :
                IADD();
                break;
            case OP_IAND :
                IAND();
                break;
            case OP_IFEQ :
                IFEQ();
                break;
            case OP_IFLT :
                IFLT();
                break;
            case OP_ICMPEQ :
                ICMPEQ();
                break;
            case OP_IINC :
                IINC();
                break;
            case OP_ILOAD :
                ILOAD();
                break;
            case OP_INVOKEVIRTUAL :
                INVOKEVIRTUAL();
                break;
            case OP_IOR :
                IOR();
                break;
            case OP_IRETURN :
                IRETURN();
                break;
            case OP_ISTORE :
                ISTORE();
                break;
            case OP_ISUB :
                ISUB();
                break;
            case OP_LDC_W :
                LDC_W();
                break;
            case OP_NOP :
                NOP();
                break;
            case OP_IN :
                IN();
            case OP_OUT :
                OUT();
                break;
            case OP_POP :
                POP();
                break;
            case OP_SWAP :
                SWAP();
                break;
            case OP_WIDE :
                WIDE();
                break;
            default:
                return 0;
                break;
        }
        return 1;
        p_counter += 1;
    }
    else { return 0; }
}

byte_t get_instruction(void) //return The value of the current instruction represented as a byte_t
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
