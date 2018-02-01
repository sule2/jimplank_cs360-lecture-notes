/* fullcat.c 
   James S. Plank
   CS360
   September, 1996 */

/* This program uses the standard io library to implement a more or less
   complete version of cat. */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 8192

int main(int argc, char **argv)
{
  int i, j;
  FILE *fd;
  char c, buf[BUFSIZE];

  if (argc == 1) {
    c = getchar();
    while (c != EOF) {
      putchar(c);
      c = getchar();
    }
  } else {
    for (j = 1; j < argc; j++) {
      fd = fopen(argv[j], "r");

      if (fd == NULL) {
        fprintf(stderr, "fullcat: %s: ", argv[j]);
        perror("");   /* Read the man page for perror */
        exit(1);
      }
      i = 1;
      while (i > 0) {
        i = fread(buf, 1, BUFSIZE, fd);
        if (i > 0) fwrite(buf, 1, i, stdout);
      }
      fclose(fd);
    }
  }
  return 0;
}
