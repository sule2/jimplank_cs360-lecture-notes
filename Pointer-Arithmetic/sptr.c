#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double d1;
  double d2;
} Two;

int main()
{
  Two iarray[10];
  Two *ip;
  int i;

  for (i = 0; i < 10; i++) { 
    iarray[i].d1 = 100+i;
    iarray[i].d2 = 200+i;
  }

  printf("iarray = 0x%lx\n", (unsigned long) iarray);

  ip = iarray;

  for (i = 0; i < 10; i++) {
    printf("i=%d.  iarray[i]={%.2lf,%.2lf}.  ip = 0x%lx.  *ip={%.2lf,%.2lf}.  (ip-iarray)=%d\n", 
        i, iarray[i].d1, iarray[i].d2, (unsigned long) ip, ip->d1, ip->d2, (int) (ip-iarray));
    ip++;
  }
}
