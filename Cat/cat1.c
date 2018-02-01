/* cat1.c 
   James S. Plank
   CS360
   September, 1996 */

/* This program uses system calls to implement a version of cat which
   prints the contents of the file specified to standard output.
   It buffers with an 8K buffer. */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 8192

int main(int argc, char **argv)
{
  int i;
  int fd;
  char buf[BUFSIZE];

  if (argc != 2) {
    fprintf(stderr, "Usage: cat1 <filename>\n");
    exit(1);
  }

  fd = open(argv[1], O_RDONLY);

  if (fd == -1) {
    fprintf(stderr, "Error: Couldn't open %s\n", argv[1]);
    exit(1);
  }

  i = 1;
  while (i > 0) {
    i = read(fd, buf, BUFSIZE);
    if (i > 0) write(1, buf, i);
  }  
  close(fd);
  return 0;
}
