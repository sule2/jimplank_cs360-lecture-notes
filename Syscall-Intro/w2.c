/* w2.c
   James S. Plank
   January, 2017
 */

/* This program opens the file "out3.txt" in the current 
   directory for writing, allows you to specify the combination
   of O_CREAT and O_TRUNC, plus what you write to the file.  */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int fd, sz, flags, len;

  if (argc != 3) {
    fprintf(stderr, "usage: w2 w|wc|wt|wct input-word\n");
    exit(1);
  }

  /* Figure out what the "flags" argument will be to the open() call. */

  if (strcmp(argv[1], "w") == 0) {
    flags = O_WRONLY;
  } else if (strcmp(argv[1], "wc") == 0) {
    flags = (O_WRONLY | O_CREAT);
  } else if (strcmp(argv[1], "wt") == 0) {
    flags = (O_WRONLY | O_TRUNC);
  } else if (strcmp(argv[1], "wct") == 0) {
    flags = (O_WRONLY | O_CREAT | O_TRUNC);
  } else {
    fprintf(stderr, "Bad first argument.  Must be one of w, wc, wt, wct.\n");
    exit(1);
  }

  /* Open the file with the given flags. */

  fd = open("out3.txt", flags, 0644);
  if (fd < 0) { perror("open"); exit(1); }

  len = strlen(argv[2]);
  sz = write(fd, argv[2], len);
  
  /* Write the input word to the file. */

  printf("called write(%d, \"%s\", %d).  It returned %d\n", fd, argv[2], len, sz);

  close(fd);
  exit(0);
}
