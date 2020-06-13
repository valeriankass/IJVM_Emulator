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

    create_stack(16);

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
    return stack.top;
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
/**
 * Check whether the machine has any more instructions to execute.
 *
 * A machine will stop running after:
 * - reaching the end of the text section
 * - encountering either the HALT/ERR instructions
 * - encountering an invalid instruction
 */
bool finished()
{
    if (&text.data[stack.size - 1] == NULL || instruction == OP_HALT || instruction == OP_ERR || instruction_is_valid()) return 1;
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
    return constant_pool.data[i];
}

int get_program_counter(void) //Returns the value of the program counter (as an offset from the first instruction).
{
    return p_counter;
}
bool step(void) //perform one instruction and return true or false
{
    instruction = get_instruction();
    switch (instruction)
    {
        case OP_BIPUSH :
            //printf("BIPUSH\n");
            BIPUSH((int8_t)text.data[p_counter + 1]);
            increase_p_counter_by(1); //might want to put it inside function BIPUSH
            break;
        case OP_DUP :
            //printf("DUP\n");
            DUP();
            break;
        case OP_ERR :
            //printf("ERR\n");
            ERR();
            break;
        case OP_GOTO :
            //printf("GOTO\n");
            increase_p_counter_by(get_offset() - 1);
            break;
        case OP_HALT :
            return false;
            break;
        case OP_IADD :
            //printf("IADD\n");
            IADD();
            break;
        case OP_IAND :
            //printf("IAND\n");
            IAND();
            break;
        case OP_IFEQ :
            //printf("IFEQ\n");
            IFEQ();
            break;
        case OP_IFLT :
            //printf("IFLT\n");
            IFLT();
            break;
        case OP_ICMPEQ :
            //printf("ICMPEQ\n");
            ICMPEQ();
            break;
        case OP_IINC :
            //printf("IINC\n");
            IINC();
            break;
        case OP_ILOAD :
            //printf("ILOAD\n");
            ILOAD();
            break;
        case OP_INVOKEVIRTUAL :
            //printf("INVOKEVIRTUAL\n");
            INVOKEVIRTUAL();
            break;
        case OP_IOR :
            //printf("IOR\n");
            IOR();
            break;
        case OP_IRETURN :
            //printf("IRETURN\n");
            IRETURN();
            break;
        case OP_ISTORE :
            //printf("ISTORE\n");
            ISTORE();
            break;
        case OP_ISUB :
            //printf("ISUB\n");
            ISUB();
            break;
        case OP_LDC_W :
            //printf("LDC_W\n");
            LDC_W();
            break;
        case OP_NOP :
            //printf("NOP\n");
            NOP();
            break;
        case OP_IN :
            //printf("IN\n");
            IN();
        case OP_OUT :
            //printf("OUT\n");
            OUT();
            break;
        case OP_POP :
            //printf("POP\n");
            POP();
            break;
        case OP_SWAP :
            //printf("SWAP\n");
            SWAP();
            break;
        case OP_WIDE :
            //printf("WIDE\n");
            WIDE();
            break;
        default:
            return 0;
            break;
    }
    increase_p_counter_by(1);
    return 1;
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
