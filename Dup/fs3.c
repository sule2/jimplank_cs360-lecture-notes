/* fs3.c
   Jim Plank
   CS360
   Dup lecture */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char s[1000];
  int i, fd;

  fd = open("file3", O_WRONLY | O_CREAT | O_TRUNC, 0644);

  i = fork();
  sprintf(s, "fork() = %d.\n", i);
  write(fd, s, strlen(s));
  close(fd);
  return 0;
}

