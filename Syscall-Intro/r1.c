/* r1.c
   James S. Plank
   September, 1996 
   Tue Jan 30 11:28:26 EST 2018
*/

/* This program shows some simple examples of using
   the system call read() to read from a file. */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  char *c;
  int fd, sz;

  /* Allocate 100 bytes, and then open in1.txt: */

  c = (char *) malloc(100 * sizeof(char));
  fd = open("in1.txt", O_RDONLY);
  if (fd < 0) { perror("r1"); exit(1); }

  /* Read ten bytes from the file.  Print the return value, 
     add the NULL character, and print the bytes as a string. */

  sz = read(fd, c, 10);
  printf("called read(%d, c, 10).  returned that %d bytes  were read.\n", fd, sz);
  c[sz] = '\0';
  printf("Those bytes are as follows: %s\n", c);

  /* Now, read 99 bytes and do the same thing.  You'll note that since there 
     were only 12 more bytes in the file, that read() returns 12.  Also, you'll
     note that read() does not NULL terminate anything.  It simply reads the
     bytes.  So you need to NULL terminate before printing. */

  sz = read(fd, c, 99);
  printf("called read(%d, c, 99).  returned that %d bytes  were read.\n", fd, sz);
  c[sz] = '\0';
  printf("Those bytes are as follows: %s\n", c);

  /* As with freeing memory, this is unnecessary, since we are exiting.
     The operating system will make sure that open files are closed when
     the process exits. */

  close(fd);
  exit(0);
}
