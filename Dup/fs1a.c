/* fs1a.c
   Jim Plank
   CS360
   Dup lecture */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

/* lseek(fd, 0, 1) returns the value of the current lseek offset */

int main()
{
  int fd1, fd2;

  fd1 = open("file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd2 = open("file1", O_WRONLY);

  printf("Before writing Jim:   lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n", 
          lseek(fd1, 0, 1), lseek(fd2, 0, 1));

  write(fd1, "Jim\n", strlen("Jim\n"));

  printf("Before writing Plank: lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n",
          lseek(fd1, 0, 1), lseek(fd2, 0, 1));

  write(fd2, "Plank\n", strlen("Plank\n"));

  printf("After writing Plank:  lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n",
          lseek(fd1, 0, 1), lseek(fd2, 0, 1));

  close(fd1);
  close(fd2);
}

