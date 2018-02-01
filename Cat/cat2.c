/* cat2.c 
   James S. Plank
   CS360
   September, 1996 */

/* This program uses the standard I/O library to implement a version of 
   cat which prints the contents of the file specified to standard output */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 8192

int main(int argc, char **argv)
{
  int i;
  FILE *fd;
  char buf[BUFSIZE];

  if (argc != 2) {
    fprintf(stderr, "Usage: cat1 <filename>\n");
    exit(1);
  }

  fd = fopen(argv[1], "r");

  if (fd == NULL) {
    fprintf(stderr, "Error: Couldn't open %s\n", argv[1]);
    exit(1);
  }

  i = 1;
  while (i > 0) {
    i = fread(buf, 1, BUFSIZE, fd);
    if (i > 0) fwrite(buf, 1, i, stdout);
  }  
  fclose(fd);
  return 0;
}
