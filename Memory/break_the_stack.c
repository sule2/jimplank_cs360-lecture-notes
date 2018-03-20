/* An infinite recursion will cause a segmentation
   violation when the stack grows bigger than the
   amount of memory allocated to it by the 
   operating system (typicallyl 8K). */

#include <stdio.h>

int main(int argc)
{
  char eight_K[8192];

  printf("Argc = %5d.  &argc = 0x%lx.\n", argc, &argc);
  main(argc+1);
  return 0;
}

