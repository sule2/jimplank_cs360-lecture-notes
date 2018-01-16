#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c;
  int i;
  float f;

  c = 'a';
  i = c;
  f = i;
  printf("c = %d (%c).   i = %d (%c).  f = %f\n", c, c, i, i, f);
  exit(0);
}

