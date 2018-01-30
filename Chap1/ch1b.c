/* ch1b.c
   James S. Plank */

/* This program prints out your user id.  Read the man page on getuid()
   for more information. */

#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("%d\n", getuid());
  return 0;
}

