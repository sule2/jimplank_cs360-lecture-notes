#include <stdio.h>
#include <stdlib.h>

int i;

int main(int argc, char **argv)
{
  int j;

  j = argc;
  i = j;
  printf("%d\n", i);
  exit(0);
}
