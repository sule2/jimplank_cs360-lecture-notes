/* o2.c
   Jim Plank
   September, 1996 
   Latest revision: Thu Jan 27 08:38:48 EST 2011
*/

/* This program attempts to opens the file "out1.txt" 
   for writing in the current directory.  Note that
   this fails because "out1.txt" does not exist already.
   See o3.c for an example of a opening "out1.txt"
   properly. */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  int fd;

  fd = open("out1.txt", O_WRONLY);
  if (fd < 0) {
    perror("out1.txt");
    exit(1);
  }
}
