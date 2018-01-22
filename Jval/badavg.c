#include <stdio.h>
#include <stdlib.h>
#include "jval.h"

int main()
{
  Jval total;
  Jval j;
  Jval n;

  n.i = 0;
  total.i = 0;
  
  while (scanf("%d", &(j.i)) == 1) {
    total.i += j.i;
    n.i++;
  }

  total.d = ((double) total.i) / ((double) n.i);

  printf("Average = %lf\n", total.d);
  exit(0);
}

