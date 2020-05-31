#include <ijvm.h>
#include <util.h>
#include <stdio.h>
#include <unistd.h>

int init_ijvm(char *binary_file)
{
  // Implement loading of binary here
  FILE *fp;
  int buf_size = 128;
  char buffer[buf_size];

  while (sizeof(binary_file) > 0)
  {
    fp = open(binary_file, "r");
    fread(buffer, sizeof(char), buf_size, fp);
    printf("The file was successfully read.");
  }

  return -1;
}

void destroy_ijvm()
{
  // Reset IJVM state
}

void run()
{
  // Step while you can
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}
