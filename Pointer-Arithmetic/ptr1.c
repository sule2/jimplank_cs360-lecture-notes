#include <stdio.h>
#include <stdlib.h>

int main()
{
  int iarray[10];
  int *ip;
  int i;

  for (i = 0; i < 10; i++) iarray[i] = 100+i;

  printf("iarray = 0x%lx\n", (unsigned long) iarray);

  ip = iarray;

  for (i = 0; i < 10; i++) {
    printf("i=%d.  iarray[i]=%d.  ip = 0x%lx.  *ip=%d.  (ip-iarray)=%d\n", 
        i, iarray[i], (unsigned long) ip, *ip, (int) (ip-iarray));
    ip++;
  }
}

