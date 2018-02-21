#include <stdio.h>

int *a(int *x)
{
  x[0] += x[2];
  return x+1;
}

int main()
{
  int array[3];
  int *ip;

  array[0] = 8;
  array[1] = 9;
  array[2] = 10;

  ip = a(array);
  (*ip)++;
}
