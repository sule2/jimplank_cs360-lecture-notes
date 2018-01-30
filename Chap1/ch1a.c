/* ch1a.c
   James S. Plank */

/* This program demonstrates an error and how errno/perror are used */

#include <stdio.h>
#include <errno.h>

int main()
{
  int i;
  FILE *f;

  f = fopen("/home/plank/noexist", "r");
  if (f == NULL) {
    printf("f = null.  errno = %d\n", errno);
    perror("/home/plank/noexist");
  }
  return 0;
}

