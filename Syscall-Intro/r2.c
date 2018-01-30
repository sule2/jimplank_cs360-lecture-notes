/* r2.c
   James S. Plank
   Tue Jan 30 11:28:26 EST 2018
*/

/* Showing what happens when you don't NULL terminate. */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
  char c[100];
  int fd;

  strcpy(c, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  fd = open("in1.txt", O_RDONLY);
  if (fd < 0) { perror("r1"); exit(1); }

  read(fd, c, 10);
  printf("%s\n", c);

  read(fd, c, 99);
  printf("%s\n", c);

  return 0;
}
