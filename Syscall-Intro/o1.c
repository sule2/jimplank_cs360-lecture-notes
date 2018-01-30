/* o1.c
   James S. Plank
   September, 1996.
   Latest revision: Thu Jan 27 08:36:03 EST 2011
 */

/* This program opens the file "in1.txt" in the current 
   directory, and prints out the return value of 
   the open() system call.  If "in1.txt" exists, open()
   will return a non-negative integer (three).  If
   "in1.txt" does not exist, then it will return -1. */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int fd;

  fd = open("in1.txt", O_RDONLY);
  printf("%d\n", fd);
  return 0;
}
