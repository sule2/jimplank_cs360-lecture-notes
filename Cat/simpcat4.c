/* simpcat4.c
   James S. Plank
   CS360
   September, 1996 */

/* This program copies standard input to standard output using read/write
   and buffering.  The buffer size is specified by the user. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int bufsize;
  char *c;
  int i;

  bufsize = atoi(argv[1]);
  c = (char *) malloc(bufsize*sizeof(char));
  i = 1;
  while (i > 0) {
    i = read(0, c, bufsize);
    if (i > 0) write(1, c, i);
  }
  return 0;
}
