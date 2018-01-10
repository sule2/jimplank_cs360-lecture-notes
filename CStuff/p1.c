#include <stdio.h>
#include <stdlib.h>

int i;

int main(int argc, char **argv)
{
  int j;

  j = argc;
  i = j;  
  printf("Argc:          %d\n", i);

  j = sizeof(long);
  printf("Sizeof(long):  %d\n", j);

  j = sizeof(int *);
  printf("Sizeof(int *): %d\n", j);

  exit(0);
}
