/* malloc() returns NULL when you run out of heap space. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc)
{
  int i;
  char *c;

  for (i = 0; i < 1000000000; i++) {
    c = (char *) malloc(1024*1024);
    printf("%9d 0x%08x\n", i, c);
    if (c == NULL) exit(0);
  }
  return 0;
}
