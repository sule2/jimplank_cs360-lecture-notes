/* fb4.c
   Jim Plank
   CS360 -- Systems Programming
   Malloc lecture #1
   October, 1996 */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int *buf;
  int i, sz;

  /* Allocate 8 memory regions with sizes 4, 8, 12, 16, 20, 24, and 28.
     Print out the integers before the return values. */

  i = 1000;
  printf("sbrk(0) = 0x%x\n", sbrk(0));
  for (sz = 4; sz < 32; sz += 4) {
    buf = (int *) malloc(sz);
    buf[0] = i;
    i++;
    printf("Allocated %d bytes.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
            sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
  }

  /* Allocate one region with a size of 100, and do the same thing. */

  sz = 100;
  buf = (int *) malloc(sz);
  buf[0] = i;
  i++;
  printf("Allocated %d bytes.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
            sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
  printf("sbrk(0) = 0x%x\n", sbrk(0));

  return 0;
}
