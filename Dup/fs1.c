/* fs1.c
   Jim Plank
   CS360
   Dup Lecture */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()
{
  int fd1, fd2;

  fd1 = open("file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd2 = open("file1", O_WRONLY);

  write(fd1, "Jim\n", strlen("Jim\n"));

  write(fd2, "Plank\n", strlen("Plank\n"));

  close(fd1);
  close(fd2);
}

