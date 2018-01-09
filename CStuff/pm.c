#include <stdio.h>
#include <stdlib.h>

int *give_me_some_ints(int n)
{
  int *p;
  int i;

  p = (int *) malloc(sizeof(int) * n);
  if (p == NULL) { fprintf(stderr, "malloc(%d) failed.\n", n); exit(1); }
  return p;
}

void fill_in_the_ints(int *a, int n)
{
  int i;

  for (i = 0; i < n; i++) a[i] = lrand48();
}

int main(int argc, char **argv)
{
  int *array;
  int size;
  int i;

  if (argc != 2) { fprintf(stderr, "usage: pm size\n"); exit(1); }
  size = atoi(argv[1]);

  array = give_me_some_ints(size);
  fill_in_the_ints(array, size);

  for (i = 0; i < size; i++) printf("%4d %10d\n", i, array[i]);
  exit(0);
}
