#include <stdio.h>
#include <stdlib.h>

int main()
{
  double iarray[10];
  double *ip;
  int i;

  for (i = 0; i < 10; i++) iarray[i] = 100+i;

  printf("iarray = 0x%lx\n", (unsigned long) iarray);

  ip = iarray;

  for (i = 0; i < 10; i++) {
    printf("i=%d.  iarray[i]=%.2lf.  ip = 0x%lx.  *ip=%.2lf.  (ip-iarray)=%d\n", 
        i, iarray[i], (unsigned long) ip, *ip, (int) (ip-iarray));
    ip++;
  }
}
