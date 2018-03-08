/* fb3.c
   James S. Plank
   CS360 -- Systems Programming
   Malloc lecture #1
   October, 1996 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int j, *buf;

  for (j = 0; j < 10; j++) {
    buf = (int *) malloc(4);
    printf("malloc(4) returned 0x%x\n", (unsigned int) buf);
  }
  return 0;
}
