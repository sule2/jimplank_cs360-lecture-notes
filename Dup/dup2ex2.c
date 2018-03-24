/* dup2ex2.c
   Jim Plank
   CS360
   Dup lecture */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
  int fd;
  char *s;

  printf("Printing this before we open anything.\n");

  fd = open("file4", O_WRONLY | O_CREAT | O_TRUNC, 0666);

  if (dup2(fd, 1) < 0) { perror("dup2"); exit(1); }

  printf("Standard output now goes to file4\n");

  close(fd);

  printf("It goes even after we closed file descriptor %d\n", fd);

  putchar('p');
  putchar('u');
  putchar('t');
  putchar('c');
  putchar('h');
  putchar('a');
  putchar('r');
  putchar(' ');
  putchar('w');
  putchar('o');
  putchar('r');
  putchar('k');
  putchar('s');
  putchar('\n');

  s = "And fwrite\n";

  fwrite(s, sizeof(char), strlen(s), stdout);

  fflush(stdout); 

  s = "And write\n";
  write(1, s, strlen(s));
}
