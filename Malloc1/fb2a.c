/* fb2a.c
   James S. Plank
   CS360 -- Systems Programming
   Malloc lecture #1
   October, 1996 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
  int *i1, *i2, *i3;

  printf("sbrk(0) before malloc(4): 0x%x\n", sbrk(0));

  i1 = (int *) malloc(4);
  printf("sbrk(0) after `i1 = (int *) malloc(4)': 0x%x\n", sbrk(0));

  i2 = (int *) malloc(4);
  printf("sbrk(0) after `i2 = (int *) malloc(4)': 0x%x\n", sbrk(0));
  printf("i1 = 0x%x, i2 = 0x%x, sbrk(0)-i2 = %d\n", (unsigned int) i1, (unsigned int) i2, 
             (unsigned int) ((char *) sbrk(0)- (char *) i2));

  i3 = (int *) malloc(1024*132);
  printf("sbrk(0) after `i3 = (int *) malloc(8164)': 0x%x\n", sbrk(0));
  printf("i3 = 0x%x\n", (unsigned int) i3);
  return 0;
}
