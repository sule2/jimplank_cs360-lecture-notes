/* simpcat.c
   Jim Plank
   September, 1996 */

/* This program is a very primitive version of "cat"
   that copies standard input to standard output one
   character at a time using the system calls read()
   and write(). */

#include <unistd.h>

int main()
{
  char c;

  while (read(0, &c, 1) == 1) write(1, &c, 1);
  return 0;
}
