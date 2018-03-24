/* fs2.c
   Jim Plank
   CS360
   Dup lecture */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int fd1, fd2;

  fd1 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd2 = dup(fd1);

  write(fd1, "Jim\n", strlen("Jim\n"));

  write(fd2, "Plank\n", strlen("Plank\n"));

  close(fd1);
  close(fd2);
}

