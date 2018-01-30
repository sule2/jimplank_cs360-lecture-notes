/* w1.c
   Jim Plank
   September, 1996 
   Latest Revision: Thu Jan 27 08:39:32 EST 2011
 */

/* This program opens the file "out3.txt" in the current 
   directory for writing, and writes the string "cs360\n"
   to it. */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  int fd, sz;

  fd = open("out3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) { perror("w1"); exit(1); }

  sz = write(fd, "cs360\n", strlen("cs360\n"));

  printf("called write(%d, \"cs360\\n\", %ld).  it returned %d\n",
         fd, strlen("cs360\n"), sz);

  close(fd);
  return 0;
}
