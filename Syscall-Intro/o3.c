/* o3.c
   Jim Plank
   September, 1996 
   Latest Revision: Thu Jan 27 08:39:06 EST 2011
 */

/* This program opens the file "out2.txt"
   for writing in the current directory.  It 
   uses O_CREAT to create the file if it does not
   exist already, and O_TRUNC to truncate the file
   to zero bytes if it does exist. */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int fd;

  fd = open("out2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("o3");
    exit(1);
  }
  return 0;
}
