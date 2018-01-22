#include <stdio.h>
#include <stdlib.h>

int main()
{
  int total;
  int j;
  int n;

  n = 0;
  total = 0;
  
  while (scanf("%d", &j) == 1) {
    total += j;
    n++;
  }

  if (n == 0) exit(1);

  printf("Average = %lf\n", ((double) total)/((double) n));
  exit(0);
}

