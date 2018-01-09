#include <stdio.h>
#include <stdlib.h>

typedef struct intdouble {
  int i;
  double d;
} ID;

int main()
{
  ID id1;

  id1.i = 5;
  id1.d = 3.14;

  printf("1: %d %.2lf\n", id1.i, id1.d);
  exit(0);
}
