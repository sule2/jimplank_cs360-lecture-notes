#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c;
  int i;
  int j;

  i = 10000;
  c = i;
  j = c;

  printf("I: %d,   J: %d,       C: %d\n", i, j, c);
  printf("I: 0x%04x,  J: 0x%04x,   C: 0x%04x\n", i, j, c);
  exit(0);
}
